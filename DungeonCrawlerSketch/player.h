#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Default values
#define MAX_PLAYER_LENGTH 5
#define ROAMING_LEFT_BOUND 0
#define ROAMING_RIGHT_BOUND 0

// Attacking values
#define ATTACKING_LEFT_BOUND -2
#define ATTACKING_RIGHT_BOUND 2
#define ATTACKING_INTERVAL 180

class Player : public Entity {
public:
    Player();
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    // maybe we can take these out and just make attacking public
    bool isAttacking( void ) const { return attacking; };

    void startAttack() {
        attacking = true;
        left_bound = ATTACKING_LEFT_BOUND;
        right_bound = ATTACKING_RIGHT_BOUND;

        for ( int i = 0; i < MAX_PLAYER_LENGTH; ++i ) {
            pixels[i].R = 0;
            pixels[i].G = 0;
            pixels[i].B = 255;
        }
    };

    void stopAttack() {
        attacking = false;
        left_bound = ROAMING_LEFT_BOUND;
        right_bound = ROAMING_RIGHT_BOUND;

        for ( int i = 0; i < MAX_PLAYER_LENGTH; ++i ) {
            pixels[i].R = 0;
            pixels[i].G = 0;
            pixels[i].B = 0;
        }

        pixels[0].G = 255;
    };

    // appearance
    Pixel pixels[MAX_PLAYER_LENGTH];

    // actions
    bool attacking = false;

    // counters
    int attacking_counter = 0;
};


#endif //DUNGEONCRAWLER_PLAYER_H
