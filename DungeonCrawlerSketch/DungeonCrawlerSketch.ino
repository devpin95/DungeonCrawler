#include <FastLED.h>
#include<Wire.h>

#include "globals.h"
#include "Player.h"

// Global variables
Player player;
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
}

void loop() {
  // put your main code here, to run repeatedly:

  //clear the board of all game objects
  FastLED.clear();

  // get the value from the accelerometer here
  getInput();
  player.setSpd(map(AcX, -20000, 20000, -3, 4));

  if ( player.getRightBoundIndex() > NUMLEDS ) {
    player.setAnchorIndex( NUMLEDS - player.getRightBound() );
  }
  
  player.updateEntity();
  drawPlayer();

  //This is where we need to have something like drawEntity(board) so it can update it
  //player.drawEntity();

  //redraw the game state
  FastLED.show();
  delay(FPS);
}

//for now I just call this to draw the player
void drawPlayer()
{
  board[player.getAnchorIndex()] = CRGB(0, 255, 0);
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
  /*Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);*/

  //Serial.println(map(AcX, -20000, 20000, -3, 4));
}

