#include <FastLED.h>

#include "globals.h"
#include "Player.h"

// Global variables
Player player;
int tempspd = 1;

//LED Strip 
CRGB board[NUMLEDS];
#define LED_DATA_PIN 6


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(board, NUMLEDS);
}

void loop() {
  // put your main code here, to run repeatedly:

  //clear the board of all game objects
  FastLED.clear();

  // get the value from the accelerometer here

  player.setSpd(tempspd);

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

