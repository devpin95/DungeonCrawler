#include <FastLED.h>
#include <Wire.h>

#include "globals.h"
#include "Player.h"
#include "Patroller.h"
#include "Lava.h"

// Global variables
Player player;
Patroller patroller( 150 );
Lava lava( 75 );
int tempspd = 1;

//LED Strip 
CRGB board[NUMLEDS];
#define LED_DATA_PIN 6

//Gyro
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;


void setup() {
    // put your setup code here, to run once:
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
    // put your main code here, to run repeatedly:

    //clear the board of all game objects
    FastLED.clear();

    // get the value from the accelerometer here
    getInput();

    if (player.isAttacking())//if player is attacking, we don't want him to move
    {
        player.setSpd(0);
    }
    else
    {
        player.setSpd(map(AcX, -20000, 20000, -3, 4));
    }

    //check for attack
    if (abs(GyY) > 20000 || abs(GyZ) > 20000)
    {
        player.startAttack();
    }

    // check for collision with the edge of the board
    if ( player.getRightBoundIndex() > NUMLEDS && player.speed > 0 )
    {
        player.stuck_right = true;
        player.setAnchorIndex( NUMLEDS - player.getRightBound() );
    }
    else if ( player.getLeftBoundIndex() < 0 && player.speed < 0 )
    {
        player.stuck_left = true;
        player.setAnchorIndex( 0 + player.getLeftBound() );
    }
    else
        {
        player.stuck_right = false;
        player.stuck_left = false;
    }

    // check for collision with enemies
    if ( player.getRightBoundIndex() >= patroller.getLeftBoundIndex()
        && player.getLeftBoundIndex() < patroller.getRightBoundIndex() )
    {
        if ( player.attacking ) {
            patroller.dead = true;
        } else {
            player.dead = true;
        }
    }

    // check for collision with lava
    if ( player.getRightBoundIndex() >= lava.getLeftBoundIndex()
         && player.getLeftBoundIndex() < lava.getRightBoundIndex() )
    {
        if ( lava.attacking ) {
            player.dead = true;
        }
    }

    // update all entities
    lava.updateEntity();
    patroller.updateEntity();
    player.updateEntity();

    // draw all entities
    lava.drawEntity( board, NUMLEDS );
    patroller.drawEntity( board, NUMLEDS );
    player.drawEntity( board, NUMLEDS );

    //redraw the game state
    FastLED.show();
    delay(FPS);
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
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  
  //Serial.println(map(AcX, -20000, 20000, -3, 4));
}

