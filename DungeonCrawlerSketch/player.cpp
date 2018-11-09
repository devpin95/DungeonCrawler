#include "player.h"

Player::Player() : Entity( ) {
    // set all of the pixels to white
    for ( int i = 0; i < PLAYER_LENGTH; ++ i ) {
        pixels[i].color = 1;
        pixels[i].index = i;
    }

    // set the anchor and boundary point
    anchor = 0;
    left_bound = 0;
    right_bound = PLAYER_LENGTH;
};

void Player::updateEntity() {
    anchor += speed;

    // update the pixel positions
    for ( int i = 0; i < PLAYER_LENGTH; ++ i ) {
        pixels[i].index = anchor + i;
    }
}

void Player::drawEntity() {
    for ( int i = 0; i < PLAYER_LENGTH; ++ i ) {
        // draw the pixel to the LED strip
    }
}