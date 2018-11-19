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
    if ( ( speed < 0 && !stuck_left ) || ( speed > 0 && !stuck_right ) ) {
        anchor += speed;
    }

    // update the pixel positions
    for ( int i = 0; i < MAX_PLAYER_LENGTH; ++ i ) {
        pixels[i].index = getAnchorIndex() + i;
    }

    if ( attacking && starting_attack ) {
        // do the startup attack animation
        ++attack_startup_counter;

        if ( attack_startup_counter < STARTUP_ATTACKING_INTERVAL ) {
            pixels[1].B += 85;
            pixels[2].B += 85;
        }
        else if ( attack_startup_counter == STARTUP_ATTACKING_INTERVAL ) {
            pixels[3].B += 85;
            pixels[4].B += 85;
            starting_attack = false;
            attack_startup_counter = 0;
        }
    }

    if ( !attacking && stopping_attack ) {
        // start fading the blue pixels away
        ++attack_shutdown_counter;
        if ( attack_shutdown_counter < 5 ) {
            pixels[4].B -= 51;
        }
        else if ( attack_shutdown_counter < 15 ) {
            pixels[3].B -= 25;
            pixels[2].B -= 25;
        }
        else if ( attack_shutdown_counter == SHUTDOWN_ATTACKING_INTERVAL ) {
            pixels[1].B -= 25;
        }
        else if ( attack_shutdown_counter > SHUTDOWN_ATTACKING_INTERVAL ) {
            stopping_attack = false;
            attack_shutdown_counter = 0;

            // reset the player to the single green pixel
            for ( int i = 0; i < MAX_PLAYER_LENGTH; ++i ) {
                pixels[i].R = 0;
                pixels[i].G = 0;
                pixels[i].B = 0;
            }

            // stop the attack at the end of the animation
            stopAttack();
        }
    }

    if ( attacking ) {
        ++attacking_counter;

        if ( attacking_counter > ATTACKING_INTERVAL ) {
            stopping_attack = true;
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
