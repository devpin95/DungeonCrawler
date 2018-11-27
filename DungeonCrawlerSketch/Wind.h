#ifndef FINAL_WIND_H
#define FINAL_WIND_H

#include <FastLED.h>
#include "Entity.h"

#define MAX_WIND_LENGTH 20
#define WIND_LEFT_BOUND 0
#define WIND_RIGHT_BOUND 20

class Wind : public Entity {
public:
    Wind( const int &spos, const int &mul );
    virtual void updateEntity() override;
    virtual void drawEntity( CRGB board[], const int &blen ) override;

    Pixel pixels[MAX_WIND_LENGTH];

    double multiplier = 0;
};

#endif //FINAL_WIND_H
