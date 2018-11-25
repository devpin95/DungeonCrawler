#include "player.h"

Player::Player() : Entity( ) {
    // set all of the pixels to white
    for ( int i = 0; i < MAX_PLAYER_LENGTH; ++ i ) {
      if (i == 0)
      {
        pixels[i].R = 0;
        pixels[i].G = 255;
        pixels[i].B = 0;
      }
      else
      {
        pixels[i].R = 0;
        pixels[i].G = 0;
        pixels[i].B = 0;
      }
        pixels[i].index = i;
    }

    // set the anchor and boundary point
    anchor = 0;
    left_bound = 0;
    right_bound = 0;
};

void Player::updateEntity() {
    if ( ( speed < 0 && !stuck_left ) || ( speed > 0 && !stuck_right ) ) {
        anchor += speed;
    }

    // update the pixel positions
    for ( int i = 0; i < MAX_PLAYER_LENGTH; ++ i ) {
        pixels[i].index = getAnchorIndex() + i;
    }


    if ( attacking ) {
        ++attacking_counter;

        if ( attacking_counter > ATTACKING_INTERVAL ) {            
            stopAttack();
        }
    }

    if ( charging )
    {
      ++charging_counter;

      if ( charging_counter > CHARGING_INTERVAL )
      {
        pixels[0].R = 0;
        pixels[0].G = 250;
        pixels[0].B = 0;
        charging = false;
        charging_counter = 0;
      }
    }
}

void Player::drawEntity( CRGB board[], const int &blen ) {
    if ( dead ) return;

    for ( int i = 0; i < MAX_PLAYER_LENGTH; ++ i ) {
        // check if the index is outside the board
        if ( pixels[i].index < 0 || pixels[i].index > blen ) {
            continue;
        }

        // check if the pixel is black
        if ( pixels[i].R == 0 && pixels[i].G == 0 && pixels[i].B == 0 ) {
            // if it is, skip it
            continue;
        }
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}
