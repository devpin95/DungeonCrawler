#ifndef FINAL_PATROLLER_H
#define FINAL_PATROLLER_H

#include <FastLED.h>
#include "Entity.h"

#define MAX_PATROLLER_LENGTH 1
#define LEFT_BOUND 0
#define RIGHT_BOUND 0

// patrol pattern
#define PATROL_SPEED 3
#define PATROL_DISTANCE 15

class Patroller : public Entity {
public:
    Patroller( const int &spos );
    void setOffset( const int &off ) { patrol += off; };
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    // appearance
    Pixel pixels[MAX_PATROLLER_LENGTH];
    bool dead = false;

    // starting position
    int starting_position;

    // counters
    int patrol = 0;
};


#endif //FINAL_PATROLLER_H
