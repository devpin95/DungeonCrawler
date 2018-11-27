#include "BigBoi.h"

BigBoi::BigBoi() {
    // set all of the pixels to white
    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        if ( i < 3 ) {
            pixels[i].R = 255;
            pixels[i].G = 255;
            pixels[i].B = 255;
        }
        else {
            pixels[i].R = 255;
            pixels[i].G = 0;
            pixels[i].B = 0;
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
        // change the position of the bigboi
        starting_position = 50;
        anchor = 50;

        firing_from_right = true;
        firing_from_left = false;

        take_damage = false;
        health -= 2;
        projectiles = BIGBOI_PROJECTILES;

        // update the pixels
        for ( int i = 0; i < BIGBOI_LENGTH; ++i ) {
            if ( i <= health ) {
                // draw the body red
                pixels[i].R = 255;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
            else if ( i <= health + BIGBOI_PROJECTILES ) {
                // draw the projectiles white
                pixels[i].R = 255;
                pixels[i].G = 255;
                pixels[i].B = 255;
                pixels[i].index = getAnchorIndex() + i;
            }
            else {
                // hide the rest
                pixels[i].R = 0;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
        }
    }
    else if (take_damage && starting_position == 50)
    {
        starting_position = 250;
        anchor = 250;

        // change the position of the bigboi
        firing_from_right = false;
        firing_from_left = true;

        take_damage = false;
        health -= 2;

        projectiles = BIGBOI_PROJECTILES;
        // update the pixels
        for ( int i = 0; i < BIGBOI_LENGTH; ++i ) {
            if ( i <= BIGBOI_PROJECTILES ) {
                // draw the projectiles white
                pixels[i].R = 255;
                pixels[i].G = 255;
                pixels[i].B = 255;
                pixels[i].index = getAnchorIndex() + i;
            }
            else if ( i <= BIGBOI_PROJECTILES + health ) {
                // draw the body red
                pixels[i].R = 255;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
            else {
                // hide the rest
                pixels[i].R = 0;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
        }
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
