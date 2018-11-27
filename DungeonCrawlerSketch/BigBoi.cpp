#include "BigBoi.h"

BigBoi::BigBoi() {
    // set all of the pixels to white
    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        if ( i < 3 ) {
            pixels[i].R = 50;
            pixels[i].G = 50;
            pixels[i].B = 50;
        }
        else {
            pixels[i].R = 255;
            pixels[i].G = 0;
            pixels[i].B = 0;
        }
        pixels[i].index = i;
    }

    // set the anchor and boundary point
    starting_position = 250;
    anchor = starting_position;
    left_bound = 0;
    right_bound = BIGBOI_LENGTH;

    // set up the projectiles
    levels[NUMLEVELS-1].numEnemies = 3;
    for ( int i = 0; i < BIGBOI_PROJECTILES; ++i ) {
        enemy[i].dead = true;
    }
}

void BigBoi::updateEntity() {
    ++patrol;
    anchor = starting_position + ( sin( patrol * 0.01 * BIGBOI_PATROL_SPEED ) * BIGBOI_PATROL_DISTANCE );

    if (take_damage && starting_position == 250)
    {
        // reset counters
        loading_counter = 0;
        shot_delay_counter = 0;

        // change the position of the bigboi
        starting_position = 50;
        anchor = 50;

        firing_to_right = true;
        firing_to_left = false;

        take_damage = false;
        health -= 2;

        projectiles = BIGBOI_PROJECTILES;
        ready_to_shoot = false;

        // update the pixels
        redraw();
    }
    else if (take_damage && starting_position == 50)
    {
        // reset counters
        loading_counter = 0;
        shot_delay_counter = 0;

        // reset position
        starting_position = 250;
        anchor = 250;

        // reset the side bigboi is shooting from
        firing_to_right = false;
        firing_to_left = true;

        // take damage
        take_damage = false;
        health -= 2;

        // reset projectiles
        projectiles = BIGBOI_PROJECTILES;
        ready_to_shoot = false;

        // update the pixels
        redraw();
    }

    ++loading_counter;
    // Counter up until we are ready to shoot
    if ( !ready_to_shoot && loading_counter == BIGBOI_START_SHOOTING ) {
        ready_to_shoot = true;
    }

    // start shooting
    if ( ready_to_shoot ) {
        ++shot_delay_counter;

        if ( projectiles == 0 ) {
            projectiles = BIGBOI_PROJECTILES;
            redraw();

            if ( firing_to_left ) {
                anchor -= BIGBOI_PROJECTILES;
            }
        }

        if ( shot_delay_counter == BIGBOI_SHOT_DELAY ) {
            shot_delay_counter = 0;
            --projectiles;

            enemy[BIGBOI_PROJECTILES - projectiles].dead = false;


            if ( firing_to_left ) {
                enemy[BIGBOI_PROJECTILES - projectiles - 1].anchor = anchor;
                enemy[BIGBOI_PROJECTILES - projectiles - 1].speed = -1;
                anchor += 1;
            }
            else if ( firing_to_right ) {
                enemy[BIGBOI_PROJECTILES - projectiles - 1].anchor = health + projectiles;
                enemy[BIGBOI_PROJECTILES - projectiles - 1].speed = 1;
            }

            redraw();

            if ( projectiles == 0 ) {
                ready_to_shoot = false;
                loading_counter = 0;
            }
        }
    }

    // Environment manipulation
    levels[NUMLEVELS-1].numEnemies = 4;
    //enemy[3].dead = false;

    if (health == 8 && !_8_health)//activate lava
    {
        _8_health = true;
        levels[NUMLEVELS-1].numLava = 1;//one biggish one in the middle
    }

    if (health == 6 && !_6_health)//activate different lava
    {
        _6_health = true;
        levels[NUMLEVELS-1].numLava = 3;//one on either side of the big one
    }

    if (health == 4 && !_4_health)//activate wind
    {
      _4_health = true;
      levels[NUMLEVELS-1].numWind = 2;//on either side of the lava
    }

    if (health == 2 && !_2_health)//add flowing lava
    {
      _2_health = true;
      levels[NUMLEVELS-1].hasLavaFlow = true;
    }

    if (health == 0)//dead
    {
      
    }

    // update the pixel positions
    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        pixels[i].index = getAnchorIndex() + i;
    }
}

void BigBoi::drawEntity( CRGB board[], const int &blen ) {
    if ( !dead ) return;

    for ( int i = 0; i < BIGBOI_LENGTH; ++ i ) {
        board[ pixels[i].index ] = CRGB( pixels[i].R, pixels[i].G, pixels[i].B );
    }
}

void BigBoi::redraw() {
    if ( firing_to_left ) {
        for ( int i = 0; i < BIGBOI_LENGTH; ++i ) {
            if ( i < projectiles ) {
                // draw the projectiles white
                pixels[i].R = 50;
                pixels[i].G = 50;
                pixels[i].B = 50;
                pixels[i].index = getAnchorIndex() + i;
            }
            else if ( i < projectiles + health ) {
                // draw the body red
                pixels[i].R = 255;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
            else {
                // hide the rest
                pixels[i].R = 0;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
        }

        left_bound = 0;
        right_bound = projectiles + health;
    }
    else if ( firing_to_right ) {
        for ( int i = 0; i < BIGBOI_LENGTH; ++i ) {
            if ( i < health ) {
                // draw the body red
                pixels[i].R = 255;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
            else if ( i < health + projectiles ) {
                // draw the projectiles white
                pixels[i].R = 50;
                pixels[i].G = 50;
                pixels[i].B = 50;
                pixels[i].index = getAnchorIndex() + i;
            }
            else {
                // hide the rest
                pixels[i].R = 0;
                pixels[i].G = 0;
                pixels[i].B = 0;
                pixels[i].index = getAnchorIndex() + i;
            }
        }

        left_bound = 0;
        right_bound = projectiles + health;
    }
}
