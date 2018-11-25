//#include <ArduinoJson.h>

#include <FastLED.h>
#include <Wire.h>

#include "globals.h"
#include "Player.h"
#include "Patroller.h"
#include "Lava.h"
#include "Enemy.h"
#include "Wind.h"
#include "levelInfo.h"

// Global variables
Player player;
//Patroller patroller[4] = { Patroller(40), Patroller(80), Patroller(160), Patroller(220) };
//Lava lava[2] = { Lava(175), Lava(125) };
//Enemy enemy[3] = { Enemy(280), Enemy(260), Enemy(240) };
//Wind wind[2] = { Wind( 50, 1 ), Wind(60, 1) };

//Entity Pools
Enemy enemy[10] = { Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0), Enemy(0) };
Patroller patroller[10] = { Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0), Patroller(0) };
Lava lava[10] = { Lava(0), Lava(0), Lava(0), Lava(0), Lava(0), Lava(0), Lava(0), Lava(0), Lava(0), Lava(0) };
Wind wind[10] = { Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1), Wind(0,1) };


//Level Check
bool levelCompleteArray[10] = { false, false, false, false, false, false, false, false, false, false };//ten levels (check if they are complete)


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
      //Serial.println(levelNum);
      
      while (levelCompleteArray[levelNum] == false)
      {
        setupLevel(levelNum);//set up the level

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
            else
            {
                AcY += 2000;//offset of gyro not being completely level
                player.speed = map(AcY, -15000, 15000, -1, 2);
            }

            //check for player attack
            if (abs(GyX) > 30000 || abs(GyY) > 30000 || abs(GyZ) > 30000)
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
                     && player.getLeftBoundIndex() < patroller[i].getRightBoundIndex()
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

            player.drawEntity( board, NUMLEDS );//PLAYER
//            death_left_runner = player.getAnchorIndex();
//            death_right_runner = player.getAnchorIndex();

            //redraw the game state
            FastLED.show();

            // if the player is dead, do the animation
            /*while ( player.dead ) {
                if ( death_left_runner == 0 && death_right_runner == NUMLEDS ) {
                    break;
                }

                if ( death_left_runner != 0 ) {
                    --death_left_runner;
                }
                if ( death_right_runner != NUMLEDS ) {
                    ++death_left_runner;
                }

                board[ death_left_runner ] = CRGB( 255, 255, 255 );
                board[ death_right_runner ] = CRGB( 255, 255, 255 );
                FastLED.show();
                delay( DEATH_FPS );
            }*/

            delay(FPS);
        }

        if (player.dead)
        {
          death_left_runner = player.anchor;
          death_right_runner = player.anchor;
          
           while (player.dead) 
           {
                if ( death_left_runner == 0 && death_right_runner == NUMLEDS ) 
                {
                    break;
                }

                if ( death_left_runner != 1 ) {
                    --death_left_runner;
                }
                if ( death_right_runner != NUMLEDS ) {
                    ++death_right_runner;
                }

                board[ death_left_runner ] = CRGB( 20, 20, 20 );
                board[ death_right_runner ] = CRGB( 20, 20, 20 );
                FastLED.show();
                delay( DEATH_FPS );
            }
        }
        else
        {
          //win animation maybe?
        }

        delay(200);//delay for level setup. ADD IN COOL RESET EFFECT
      }
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

