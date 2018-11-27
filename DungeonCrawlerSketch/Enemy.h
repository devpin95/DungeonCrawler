#ifndef FINAL_ENEMY_H
#define FINAL_ENEMY_H

#include <FastLED.h>
#include "Entity.h"

#define MAX_ENEMY_LENGTH 1
#define ENEMY_LEFT_BOUND 0
#define ENEMY_RIGHT_BOUND 0

// patrol pattern
#define PATROL_SPEED 2
#define PATROL_DISTANCE 10

class Enemy : public Entity {
    public:
    Enemy( const int &spos );
    virtual void updateEntity() override;
    virtual void drawEntity( CRGB board[], const int &blen ) override;

    // appearance
    Pixel pixels[MAX_ENEMY_LENGTH];
    bool dead = false;
    bool sleeping = true;

    int sleep_delay = 0;
    int sleep_counter = 0;

    int enemy_speed = -1;
};


#endif //FINAL_ENEMY_H
