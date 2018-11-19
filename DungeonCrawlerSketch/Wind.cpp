#include "Wind.h"

Wind::Wind( const int &spos, const double &mul ) : Entity( ) {
    // set all of the pixels to white
    for ( int i = 0; i < MAX_WIND_LENGTH; ++ i ) {
        pixels[i].R = 255 - (i*10);
        pixels[i].G = 255;
        pixels[i].B = 255;
        pixels[i].index = spos + i;
    }

    // set the anchor and boundary point
    anchor = spos;
    left_bound = WIND_LEFT_BOUND;
    right_bound = WIND_RIGHT_BOUND;
    multiplier = mul;
};

void Wind::updateEntity() {
    if ( multiplier >= 0 )
    {
        int tempr = pixels[MAX_WIND_LENGTH-1].R;
        int tempg = pixels[MAX_WIND_LENGTH-1].G;
        int tempb = pixels[MAX_WIND_LENGTH-1].B;

        for ( int i = MAX_WIND_LENGTH; i > 0; --i ) {
            if ( i == 0 ) {
                pixels[i].R = tempr;
                pixels[i].G = tempg;
                pixels[i].B = tempb;
            }
            pixels[i].R = pixels[i-1].R;
            pixels[i].G = pixels[i-1].G;
            pixels[i].B = pixels[i-1].B;
        }
    }
    else
    {
        int tempr = pixels[0].R;
        int tempg = pixels[0].G;
        int tempb = pixels[0].B;

        for ( int i = 0; i < MAX_WIND_LENGTH; ++i ) {
            if ( i == MAX_WIND_LENGTH-1 ) {
                pixels[i].R = tempr;
                pixels[i].G = tempg;
                pixels[i].B = tempb;
            }
            pixels[i].R = pixels[i+1].R;
            pixels[i].G = pixels[i-+1].G;
            pixels[i].B = pixels[i-+1].B;
        }
    }
}

void Wind::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < MAX_WIND_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}