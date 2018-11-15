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
    right_bound = MAX_PLAYER_LENGTH;
};

void Player::updateEntity() {
    anchor += speed;

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
}

void Player::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < MAX_PLAYER_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}
