#ifndef FINAL_WIND_H
#define FINAL_WIND_H

#include <FastLED.h>
#include "Entity.h"

#define MAX_WIND_LENGTH 10
#define WIND_LEFT_BOUND 0
#define WIND_RIGHT_BOUND 10

class Wind : public Entity {
public:
    Wind( const int &spos, const double &mul );
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    Pixel pixels[MAX_WIND_LENGTH];

    double multiplier = 0;
};

#endif //FINAL_WIND_H
