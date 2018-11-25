#ifndef PLAYER_H
#define PLAYER_H

#include <FastLED.h>
#include "Entity.h"

// Default values
#define MAX_PLAYER_LENGTH 5
#define ROAMING_LEFT_BOUND 0
#define ROAMING_RIGHT_BOUND 0

// Attacking values
#define ATTACKING_LEFT_BOUND -2
#define ATTACKING_RIGHT_BOUND 2
#define ATTACKING_INTERVAL 20
#define STARTUP_ATTACKING_INTERVAL 5
#define SHUTDOWN_ATTACKING_INTERVAL 10
#define CHARGING_INTERVAL 30

class Player : public Entity {
public:
    Player();
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    // maybe we can take these out and just make attacking public
    bool isAttacking( void ) const { return attacking; };

    void startAttack() {
        starting_attack = true;
        charging = true;

        if ( attacking ) {
            attacking_counter = 0;
            starting_attack = false;
            return;
        }

        stopping_attack = false;
        attacking = true;
        left_bound = ATTACKING_LEFT_BOUND;
        right_bound = ATTACKING_RIGHT_BOUND;

        // set the single pixel to blue
//        pixels[0].R = 0;
//        pixels[0].G = 0;
//        pixels[0].B = 255;

        for ( int i = 0; i < MAX_PLAYER_LENGTH; ++i ) {
            pixels[i].R = 0;
            pixels[i].G = 0;
            pixels[i].B = 250;
        }
    };

    void stopAttack() {
        stopping_attack = true;
        attacking = false;
        starting_attack = false;
        left_bound = ROAMING_LEFT_BOUND;
        right_bound = ROAMING_RIGHT_BOUND;

        for ( int i = 0; i < MAX_PLAYER_LENGTH; ++i ) {
            pixels[i].R = 0;
            pixels[i].G = 0;
            pixels[i].B = 0;
        }

        attacking_counter = 0;
        pixels[0].R = 180;
        pixels[0].G = 0;
        pixels[0].B = 180;
    };

    // appearance
    Pixel pixels[MAX_PLAYER_LENGTH];
    bool dead = false;

    // actions
    bool attacking = false;
    bool starting_attack = false;
    bool stopping_attack = false;
    bool charging = false;

    // movement contitions
    bool stuck_left = false;
    bool stuck_right = false;

    // counters
    int attacking_counter = 0;
    int attack_startup_counter = 0;
    int attack_shutdown_counter = 0;
    int charging_counter = 0;
};


#endif //DUNGEONCRAWLER_PLAYER_H
