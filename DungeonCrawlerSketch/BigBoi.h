#ifndef FINAL_BIGBOI_H
#define FINAL_BIGBOI_H

#include <FastLED.h>
#include "Entity.h"

#define BIGBOI_LENGTH 16
#define BIGBOI_PATROL_SPEED 2
#define BIGBOI_PATROL_DISTANCE 20

class BigBoi : public Entity {
public:
    BigBoi();
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    Pixel pixels[BIGBOI_LENGTH];

    // boss attributes
    int health = 10;
    bool alive = true;
    bool firing_from_left = true;
    bool firing_from_right = false;
    bool take_damage = false;

    // positioning
    int starting_position = 0;

    // counters
    int patrol = 0;
};


#endif //FINAL_BIGBOI_H
