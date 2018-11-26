#include "BigBoi.h"

BigBoi::BigBoi() {
    // set all of the pixels to white
    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        if ( i < 3 ) {
            pixels[i].R = 255;
            pixels[i].G = 0;
            pixels[i].B = 0;
        }
        else {
            pixels[i].R = 255;
            pixels[i].G = 255;
            pixels[i].B = 255;
        }
        pixels[i].index = i;
    }

    // set the anchor and boundary point
    starting_position = 250;
    anchor = starting_position;
    left_bound = 0;
    right_bound = BIGBOI_LENGTH;
}

void BigBoi::updateEntity() {
    ++patrol;
    anchor = starting_position + ( sin( patrol * 0.01 * BIGBOI_PATROL_SPEED ) * BIGBOI_PATROL_DISTANCE );

    if (take_damage && starting_position == 250)
    {
      starting_position = 50;
      take_damage = false;
      health -= 2;
    }
    else if (take_damage && starting_position == 50)
    {
      starting_position = 250;
      take_damage = false;
      health -= 2;
    }

    // update the pixel positions
    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        pixels[i].index = getAnchorIndex() + i;
    }
}

void BigBoi::drawEntity( CRGB board[], const int &blen ) {
    if ( !alive ) return;

    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}
