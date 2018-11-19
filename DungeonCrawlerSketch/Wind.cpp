#include "Wind.h"

Wind::Wind( const int &spos, const double &mul ) : Entity( ) {
    // set all of the pixels to white
    for ( int i = 0; i < MAX_WIND_LENGTH; ++ i ) {
        pixels[i].R = 150;
        pixels[i].G = 150;
        pixels[i].B = 150;
        pixels[i].index = spos + i;
    }

    // set the anchor and boundary point
    anchor = spos;
    left_bound = WIND_LEFT_BOUND;
    right_bound = WIND_RIGHT_BOUND;
    multiplier = mul;
};

void Wind::updateEntity() {

}
void Wind::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < MAX_WIND_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}