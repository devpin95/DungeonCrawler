#ifndef DUNGEONCRAWLER_LEVELS_H
#define DUNGEONCRAWLER_LEVELS_H

/*
 * Struct will contain information about each level in the order:
 *      numEnemy, enemyPositions
 *      numPatroller, patrollerPositions
 *      numLava, lavaPositions
 */

struct Level
{
    int playerPos;
    
    int numEnemies;// = 0;
    int enemyPos[20];// = { 0 };
    int enemyDelay[20];// = { 0 };
    
    int numPatrollers;// = 0;
    int patrollerPos[20];// = { 0 };
    int patrollerOffset[20];// = { 0 };
    
    int numLava;// = 0;
    int lavaPos[20];// = { 0 };
    int lavaLength[20];// = { 0 };
    //int lavaDelay[20] = { 0 };
    
    int numWind;// = 0;
    int windPos[20];// = { 0 };
    int windDir[20];// = { 0 };
};


Level levels[NUMLEVELS] =
{
    {   // Level 1
        0,
        1, {250}, {0},
        0, {0}, {0},
        0, {0}, {0},
        0, {0}, {0}
    },
    {   // Level 2
        20,
        1, {250}, {0},
        1, {150}, {0},
        3, {150, 160, 170}, {10, 10, 10},
        2, {30, 40}, {1, 1}
    },
    {   // Level 3
        20,
        5, {100, 105, 110, 115, 120}, {0, 10, 20, 30, 40},
        3, {150, 155, 160}, {0, 100, 200},
        1, {290}, {30},
        4, {30, 40, 50, 60}, {1, 1, 1, 1}
    }
};


#endif //DUNGEONCRAWLER_LEVELS_H
