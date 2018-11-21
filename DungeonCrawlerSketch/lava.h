#ifndef FINAL_LAVA_H
#define FINAL_LAVA_H

#define MAX_LAVA_LENGTH 10

#define LAVA_ATTACKING_INTERVAL 120

#define LAVA_SPEED 30

#include <FastLED.h>
#include "Entity.h"

class Lava : public Entity {
public:
    Lava( int spos );
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    void startAttack() {
        attacking = true;
        for ( int i = 0; i < MAX_LAVA_LENGTH; ++i ) {
            pixels[i].R = 255;
            pixels[i].G = 69;
            pixels[i].B = 0;
        }
    };

    void stopAttack() {
        attacking = false;
        for ( int i = 0; i < MAX_LAVA_LENGTH; ++i ) {
            pixels[i].R = 30;
            pixels[i].G = 5;
            pixels[i].B = 0;
        }
    };

    Pixel pixels[MAX_LAVA_LENGTH];

    // actions
    bool attacking = false;

    // counters
    int attacking_counter = 0;
};


#endif //FINAL_LAVA_H
