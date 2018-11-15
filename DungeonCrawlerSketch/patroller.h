#ifndef FINAL_PATROLLER_H
#define FINAL_PATROLLER_H

#include <FastLED.h>
#include "Entity.h"

#define MAX_PATROLLER_LENGTH 1
#define LEFT_BOUND 0
#define RIGHT_BOUND 0

// patrol pattern
#define PATROL_SPEED 2
#define PATROL_DISTANCE 10

class Patroller : public Entity {
public:
    Patroller( int spos );
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    // appearance
    Pixel pixels[MAX_PATROLLER_LENGTH];

    // starting position
    int starting_position;

    // counters
    int patrol = 0;
};


#endif //FINAL_PATROLLER_H
