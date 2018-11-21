#ifndef DUNGEONCRAWLER_LEVELS_H
#define DUNGEONCRAWLER_LEVELS_H


#include "Enemy.h"
#include "patroller.h"
#include "lava.h"

/*
 * Struct will contain information about each level in the order:
 *      Enemy, enemyPositions
 *      Patroller, patrollerPositions
 *      Lava, lavaPositions
 */


struct Level
{
    Enemy enemies[10];
};


#endif //DUNGEONCRAWLER_LEVELS_H
