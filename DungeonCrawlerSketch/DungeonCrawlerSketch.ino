#include "globals.h"
#include "Player.h"

// Global variables
Player player;
int tempspd = 2;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  // get the value from the accelerometer here

  player.setSpd(tempspd);

  if ( player.getRightBoundIndex() > NUMLEDS ) {
    player.setAnchorIndex( NUMLEDS - player.getRightBound() );
  }
  
  player.updateEntity();

  player.drawEntity();
  
  delay(FPS);
}
