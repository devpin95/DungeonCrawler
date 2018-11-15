#include "patroller.h"

Patroller::Patroller( int spos ) : Entity( ) {
    // set all of the pixels to white
    for ( int i = 0; i < MAX_PATROLLER_LENGTH; ++ i ) {
        pixels[i].R = 255;
        pixels[i].G = 0;
        pixels[i].B = 0;
        pixels[i].index = i;
    }

    // set the anchor and boundary point
    starting_position = spos;
    anchor = spos;
    left_bound = 0;
    right_bound = MAX_PATROLLER_LENGTH;
};

void Patroller::updateEntity() {
    ++patrol;
    anchor = starting_position + ( sin( patrol * 0.01 * PATROL_SPEED ) * PATROL_DISTANCE );

    // update the pixel positions
    for ( int i = 0; i < MAX_PATROLLER_LENGTH; ++ i ) {
        pixels[i].index = getAnchorIndex() + i;
    }
}

void Patroller::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < MAX_PATROLLER_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}
