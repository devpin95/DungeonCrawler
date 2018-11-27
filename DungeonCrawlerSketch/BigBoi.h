#ifndef FINAL_BIGBOI_H
#define FINAL_BIGBOI_H

#include <FastLED.h>
#include "Entity.h"
#include "globals.h"
#include "Level.h"
#include "Enemy.h"

#define BIGBOI_LENGTH 13
#define BIGBOI_PATROL_SPEED 2
#define BIGBOI_PATROL_DISTANCE 20

#define BIGBOI_PROJECTILES 3

extern Level levels[NUMLEVELS];
extern Enemy enemy[POOL_NUMENEMIES];


class BigBoi : public Entity {
public:
    BigBoi();
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    void redraw();
    void resetBigBoi() {};

    Pixel pixels[BIGBOI_LENGTH];

    // boss attributes
    int health = 10;
    bool alive = true;
    bool firing_to_left = true;
    bool firing_to_right = false;
    bool take_damage = false;

    // positioning
    int starting_position = 0;

    int projectiles = 3;

    // counters
    int patrol = 0;
};


#endif //FINAL_BIGBOI_H
