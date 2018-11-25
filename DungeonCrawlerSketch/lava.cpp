#include "lava.h"

Lava::Lava( const int &spos ) : Entity( ) {
    pixels = new Pixel[lava_length];

    for ( int i = 0; i < lava_length; ++ i ) {
        pixels[i].R = 255;
        pixels[i].G = 69;
        pixels[i].B = 0;
        pixels[i].index = spos + i;
    }

    // set the anchor and boundary point
    anchor = spos;
    left_bound = 0;
    right_bound = lava_length;
};

void Lava::setLength( const int &len ) {
    delete[] pixels;
    lava_length = len;
    pixels = new Pixel[lava_length];

    for ( int i = 0; i < lava_length; ++ i ) {
        pixels[i].R = 255;
        pixels[i].G = 69;
        pixels[i].B = 0;
        pixels[i].index = getAnchorIndex() + i;
    }

    right_bound = lava_length;
}

void Lava::updateEntity() {
    ++attacking_counter;

    if ( attacking_counter < attack_delay ) {
        return;
    }

    if ( !attacking && sin(attacking_counter * 0.001 * LAVA_SPEED) > 0.5)
    {
      startAttack();
    }
    else if (attacking && sin(attacking_counter * 0.001 * LAVA_SPEED) < 0.5)
    {
      stopAttack();
    }

    /*if ( !attacking && attacking_counter == LAVA_ATTACKING_INTERVAL ) {
        startAttack();
    }
    if ( attacking && attacking_counter == LAVA_ATTACKING_INTERVAL ) {
        stopAttack();
    }*/
}
void Lava::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < lava_length; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}
