#ifndef FINAL_BIGBOI_H
#define FINAL_BIGBOI_H

#include <FastLED.h>
#include "Entity.h"
#include "globals.h"
#include "Level.h"
#include "Enemy.h"
#include "patroller.h"
#include "lava.h"
#include "Wind.h"

#define BIGBOI_LENGTH 13
#define BIGBOI_PATROL_SPEED 2
#define BIGBOI_PATROL_DISTANCE 20

#define BIGBOI_PROJECTILES 3
#define BIGBOI_START_SHOOTING 120
#define BIGBOI_SHOT_DELAY 50

// extern in the pool arrays
extern Level levels[NUMLEVELS];
extern Enemy enemy[POOL_NUM_ENEMIES];
extern Patroller patroller[POOL_NUM_PATROLLERS];
extern Lava lava[POOL_NUM_LAVA];
extern Wind wind[POOL_NUM_WIND];

class BigBoi : public Entity {
public:
    BigBoi();
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    void redraw();
    void reset() {
        starting_position = 250;
        anchor = 250;
        health = 10;
        firing_to_left = true;
        firing_to_right = false;
        loading_counter = 0;
        shot_delay_counter = 0;
        projectiles = BIGBOI_PROJECTILES;
        bool _8_health = false;
        bool _6_health = false;
        bool _4_health = false;
        bool _2_health = false;

        for (int i = 0; i < POOL_NUM_ENEMIES; i++)
        {
          enemy[i].dead = true;
        }
    };

    Pixel pixels[BIGBOI_LENGTH];

    // boss attributes
    int health = 10;
    bool dead = false;
    bool firing_to_left = true;
    bool firing_to_right = false;
    bool take_damage = false;
    bool _8_health = false;
    bool _6_health = false;
    bool _4_health = false;
    bool _2_health = false;

    bool ready_to_shoot = true;

    // positioning
    int starting_position = 0;
    int loading_counter = 0;
    int shot_delay_counter = 0;
    int projectiles = 3;

    // counters
    int patrol = 0;
};


#endif //FINAL_BIGBOI_H
