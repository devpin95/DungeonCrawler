#include "Enemy.h"

Enemy::Enemy( const int &spos ) : Entity() {
    // set all of the pixels to white
    for ( int i = 0; i < MAX_ENEMY_LENGTH; ++ i ) {
        pixels[i].R = 255;
        pixels[i].G = 0;
        pixels[i].B = 0;
        pixels[i].index = spos + i;
    }

    // set the anchor and boundary point
    anchor = spos;
    left_bound = ENEMY_LEFT_BOUND;
    right_bound = ENEMY_RIGHT_BOUND;
}

void Enemy::updateEntity() {
    ++sleep_counter;

    if ( sleep_counter >= sleep_delay && sleeping == true) {
        sleeping = false;
    }

    if ( !dead && !sleeping ) {
        anchor += enemy_speed;
    }

    // update the pixel positions
    for ( int i = 0; i < MAX_ENEMY_LENGTH; ++ i ) {
        pixels[i].index = getAnchorIndex() + i;
    }
}

void Enemy::drawEntity( CRGB board[], const int &blen ) {
    if ( dead || sleeping ) return;

    for ( int i = 0; i < MAX_ENEMY_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}
