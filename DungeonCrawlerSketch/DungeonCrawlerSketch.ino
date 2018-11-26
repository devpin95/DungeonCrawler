//#include <ArduinoJson.h>

#include <FastLED.h>
#include <Wire.h>

#include "globals.h"
#include "Player.h"
#include "Patroller.h"
#include "Lava.h"
#include "Enemy.h"
#include "Wind.h"
#include "FlowingLava.h"
#include "levelInfo.h"
#include "BigBoi.h"

// Global variables
Player player;
//Patroller patroller[4] = { Patroller(40), Patroller(80), Patroller(160), Patroller(220) };
//Lava lava[2] = { Lava(175), Lava(125) };
//Enemy enemy[3] = { Enemy(280), Enemy(260), Enemy(240) };
//Wind wind[2] = { Wind( 50, 1 ), Wind(60, 1) };

//Entity Pools
Enemy enemy[10] = { Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0) };
Patroller patroller[10] = { Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0) };
Lava lava[5] = { Lava(0), Lava(0), Lava(0), Lava(0), Lava(0) };
Wind wind[5] = { Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1) };
FlowingLava flowinglava;
BigBoi bigboi;

//Level Check
bool levelCompleteArray[NUMLEVELS] = { false };//ten levels (check if they are complete)


#include "utilityFunctions.h"


//LED Strip 
CRGB board[NUMLEDS];
#define LED_DATA_PIN 6

//Gyro
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;


void setup() {
    //LED Strip
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(board, NUMLEDS);

    //Gyroscope
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    //Serial.begin(9600);
}


void loop() {
    //Serial.println("LOOP");

    // put your main code here, to run repeatedly:
    for (int levelNum = 0; levelNum < NUMLEVELS; ++levelNum)
    {            
      while (levelCompleteArray[levelNum] == false)
      {
        setupLevel(levelNum);//set up the level

        //if it is the final level, set all the numbers of entities to 0
        //this way, the boss will have control over what gets shown
        if (levelNum == NUMLEVELS - 1)
        {
            levels[levelNum].numEnemies = 0;
            levels[levelNum].numPatrollers = 0;
            levels[levelNum].numLava = 0;
            levels[levelNum].numWind = 0;
        }

        while (!player.dead && levelCompleteArray[levelNum] == false)//check for if the player is alive and has not yet completed the level
        {
            //*********************GAME STUFF***************************
            //clear the board of all game objects
            FastLED.clear();

            //get the value from the accelerometer
            getInput();

            if (player.isAttacking())//if player is attacking, we don't want him to move
            {
                player.speed = 0;
            }
            else//PLAYER MOVEMENT
            {
//                AcY += 6000;//offset of gyro not being completely level
//                player.speed = map(AcY, -15000, 15000, -2, 2) * 0.5;
                int tempAcY = AcY + 1000;
                if (tempAcY > -3000 && tempAcY < 3000)
                {
                  player.speed = 0;
                }

                if (tempAcY > 3000)
                {
                  player.speed = 0.2;
                }
                if (tempAcY > 8000)
                {
                  player.speed = 0.6;
                }
                if (tempAcY > 12000)
                {
                  player.speed = 1;
                }

                if (tempAcY < -3000)
                {
                  player.speed = -0.2;
                }
                if (tempAcY < -8000)
                {
                  player.speed = -0.6;
                }
                if (tempAcY < -12000)
                {
                  player.speed = -1;
                }
            }

            //check for if player attacks and he is not charging
            if ((abs(GyX) > 32000 || abs(GyY) > 32000 || abs(GyZ) > 32000) && !player.charging)
            {
                player.startAttack();
            }

            // check for collision with the edge of the board
            if ( player.getRightBoundIndex() > NUMLEDS && player.speed > 0 )//check end of board
            {
                player.stuck_right = true;
                player.setAnchorIndex( NUMLEDS - player.getRightBound() );
            }
            else if ( player.getLeftBoundIndex() < 0 && player.speed < 0 )//check beginning of board
            {
                player.stuck_left = true;
                player.setAnchorIndex( 0 + player.getLeftBound() );
            }
            else
            {
                player.stuck_right = false;
                player.stuck_left = false;
            }

            // check for if player made it to end of the board (WIN)
            if ( player.anchor > 290)
            {
                levelCompleteArray[levelNum] = true;//got to the end (LEVEL COMPLETE)            
            }


            //COLLISIONS
            for (int i = 0; i < levels[levelNum].numEnemies; ++i)//ENEMIES
            {
                if ( player.getRightBoundIndex() >= enemy[i].getLeftBoundIndex()
                     && !enemy[i].dead )
                {
                    if ( player.attacking ) {
                        enemy[i].dead = true;
                    } else {
                        player.dead = true;
                    }
                }
            }
            for (int i = 0; i < levels[levelNum].numPatrollers; ++i)//PATROLLERS
            {
                if ( player.getRightBoundIndex() >= patroller[i].getLeftBoundIndex()
                     && player.getLeftBoundIndex() <= patroller[i].getRightBoundIndex()
                     && !patroller[i].dead )
                {
                    if ( player.attacking ) {
                        patroller[i].dead = true;
                    } else {
                        player.dead = true;
                    }
                }
            }
            for (int i = 0; i < levels[levelNum].numLava; ++i)//LAVA
            {
                if ( player.getRightBoundIndex() >= lava[i].getLeftBoundIndex()
                     && player.getLeftBoundIndex() < lava[i].getRightBoundIndex() )
                {
                    if ( lava[i].attacking ) {
                        player.dead = true;
                    }
                }
                //check for if enemies are within lava bounds
            }
            for (int i = 0; i < levels[levelNum].numWind; ++i)//WIND
            {
                if ( player.getRightBoundIndex() >= wind[i].getLeftBoundIndex()
                     && player.getLeftBoundIndex() < wind[i].getRightBoundIndex() )
                {
                    if ( !player.attacking ) {
                        player.speed += wind[i].multiplier;
                    }
                }
            }
            if ( levels[levelNum].hasLavaFlow ) 
            {
                if (player.anchor <= flowinglava.flowhead)
                {
                    player.dead = true;
                }
            }
            if ( levelNum == NUMLEVELS - 1 )//if it is the final level, check if the player hit the boss OR the boss killed the player
            {
                if (player.getRightBoundIndex() >= bigboi.getLeftBoundIndex()
                    && player.getLeftBoundIndex() < bigboi.getRightBoundIndex() )
                {
                  if ( player.attacking ){
                    bigboi.take_damage = true;
                  } else {
                    player.dead = true;
                  }
                }
            }


            //UPDATE ENTITIES
            //environment
            for (int i = 0; i < levels[levelNum].numLava; ++i)//LAVA
            {
                lava[i].updateEntity();
            }
            for (int i = 0; i < levels[levelNum].numWind; ++i)//WIND
            {
                wind[i].updateEntity();
            }
            //enemies
            for (int i = 0; i < levels[levelNum].numEnemies; ++i)//ENEMY
            {
                enemy[i].updateEntity();
            }
            for (int i = 0; i < levels[levelNum].numPatrollers; ++i)//PATROLLER
            {
                patroller[i].updateEntity();
            }
            if ( levels[levelNum].hasLavaFlow ) 
            {
                flowinglava.updateEntity();
            }
            if ( levelNum == NUMLEVELS - 1 )//if it is the final level
            {
                bigboi.updateEntity();
            }

            player.updateEntity();//PLAYER


            //DRAW ALL ENTITIES
            //environment
            for (int i = 0; i < levels[levelNum].numLava; ++i)//LAVA
            {
                lava[i].drawEntity( board, NUMLEDS );
            }
            for (int i = 0; i < levels[levelNum].numWind; ++i)//WIND
            {
                wind[i].drawEntity( board, NUMLEDS );
            }
            //enemies
            for (int i = 0; i < levels[levelNum].numPatrollers; ++i)//PATROLLER
            {
                patroller[i].drawEntity( board, NUMLEDS );
            }
            for (int i = 0; i < levels[levelNum].numEnemies; ++i)//ENEMY
            {
                enemy[i].drawEntity( board, NUMLEDS );
            }
            if ( levels[levelNum].hasLavaFlow ) 
            {
                flowinglava.drawEntity( board, NUMLEDS );
            }
            if ( levelNum == NUMLEVELS - 1 )//if it is the final level
            {
                bigboi.drawEntity( board, NUMLEDS );
            }

            player.drawEntity( board, NUMLEDS );//PLAYER

            //redraw the game state
            FastLED.show();

            delay(FPS);
        }

        //if the player dies, we need the death animation
        if (player.dead)
        {
          FastLED.clear();
          
          death_left_runner = player.anchor;
          death_right_runner = player.anchor;

          for (int x = 0; x < 20; ++x)
          {
            if (death_left_runner > 0)
            { death_left_runner--; }

            if (death_right_runner < NUMLEDS)
            { death_right_runner++; }
            
            board[ death_left_runner ] = CRGB( 0, 80-4*x, 0 );
            board[ death_right_runner ] = CRGB( 0, 80-4*x, 0 );
          
              
            FastLED.show();
            delay( DEATH_FPS );
          }

          delay( 500 );
        }
        else//if the player is alive, we do the next level animation
        {                   
          int alpha = 15;
          if (levelNum + 1 < NUMLEVELS)//so we do the animation for levels that aren't the last level
          {          
              FastLED.clear();
              //move the player back to the new starting position
              for (int x = player.anchor; x > levels[levelNum+1].playerPos; --x)
              {
                //FastLED.clear();
                                
                board[ x ] = CRGB( 0, 250, 0 );//player
                board[ x+1 ] = CRGB( 0, 0, 0 );
                board[ x+2 ] = CRGB( 0, 0, 0 );
                board[ x+3 ] = CRGB( 0, 0, 0 );
                board[ x+4 ] = CRGB( 0, 0, 0 );
                board[ x+5 ] = CRGB( alpha, alpha, alpha);

                FastLED.show();
                delay(WIN_FPS);
              }

//              for (int x = levels[levelNum+1].playerPos + 5; x < NUMLEDS; ++x)
//              {
//                board[ x ] = CRGB( 0, 0, 0 );
//                FastLED.show();
//                //delay(WIN_FPS/2);
//              }
          }
          else
          {
              FastLED.clear();
              //move the player back to the new starting position of the first level
              for (int x = player.anchor; x > levels[0].playerPos; --x)
              {
                //FastLED.clear();
                                
                board[ x ] = CRGB( 0, 250, 0 );//player
                board[ x+1 ] = CRGB( 0, 0, 0 );
                board[ x+2 ] = CRGB( 0, 0, 0 );
                board[ x+3 ] = CRGB( 0, 0, 0 );
                board[ x+4 ] = CRGB( 0, 0, 0 );
                board[ x+5 ] = CRGB( 15, 15, 0 );

                FastLED.show();
                delay(WIN_FPS);
              }

              for (int x = levels[0].playerPos + 5; x < NUMLEDS; ++x)
              {
                board[ x ] = CRGB( 0, 0, 0 );
                FastLED.show();
                //delay(WIN_FPS/2);
              }
          }
          
        }

        //delay(200);//delay for level setup. ADD IN COOL RESET EFFECT
      }
    }

    //RESET to play all levels again
    for (int i = 0; i < NUMLEVELS; ++i)
    {
      levelCompleteArray[i] = false;
    }
}


void getInput()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  Serial.print("AcX = "); Serial.print(AcX);
//  Serial.print(" | AcY = "); Serial.print(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
  
  //Serial.println(map(AcX, -20000, 20000, -3, 4));
}


