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
}

void BigBoi::updateEntity() {
    ++patrol;
    anchor = starting_position + ( sin( patrol * 0.01 * BIGBOI_PATROL_SPEED ) * BIGBOI_PATROL_DISTANCE );

    if (take_damage && starting_position == 250)
    {
        // change the position of the bigboi
        starting_position = 50;
        anchor = 50;

        firing_to_right = true;
        firing_to_left = false;

        take_damage = false;
        health -= 2;
        projectiles = BIGBOI_PROJECTILES;

        // update the pixels
        redraw();
    }
    else if (take_damage && starting_position == 50)
    {
        starting_position = 250;
        anchor = 250;

        // change the position of the bigboi
        firing_to_right = false;
        firing_to_left = true;

        take_damage = false;
        health -= 2;

        projectiles = BIGBOI_PROJECTILES;
        // update the pixels
        redraw();
    }

    levels[NUMLEVELS-1].numEnemies = 4;
    enemy[3].dead = false;

    if (health == 8 && !8_health)//activate lava
    {
        8_health = true;
        levels[NUMLEVELS-1].numLava = 1;//one biggish one in the middle
    }

    if (health == 6 && !6_health)//activate different lava
    {
        6_health = true;
        levels[NUMLEVELS-1].numLava = 3;//one on either side of the big one
    }

    if (health == 4 && !4_health)//activate wind
    {
      4_health = true;
      levels[NUMLEVELS-1].numWind = 2;//on either side of the lava
    }

    if (health == 2 && !2_health)//add flowing lava
    {
      2_health = true;
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
    if ( !alive ) return;

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
