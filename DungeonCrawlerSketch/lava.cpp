#include "lava.h"

Lava::Lava( int spos ) : Entity( ) {
    // set all of the pixels to white
    for ( int i = 0; i < MAX_LAVA_LENGTH; ++ i ) {
        pixels[i].R = 255;
        pixels[i].G = 140;
        pixels[i].B = 0;
        pixels[i].index = i;
    }

    // set the anchor and boundary point
    anchor = spos;
    left_bound = 0;
    right_bound = MAX_LAVA_LENGTH;
};

void Lava::updateEntity() {
    ++attacking_counter;

    if ( !attacking && attacking_counter == ATTACKING_INTERVAL ) {
        startAttack();
    }
    if ( attacking && attacking_counter == ATTACKING_INTERVAL ) {
        stopAttack();
    }
}
void Lava::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < MAX_LAVA_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}