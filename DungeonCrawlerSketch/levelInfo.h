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
        0,                                                //player position
        4, {250, 250, 250, 250}, {0, 100, 200, 300},         //numEnemies, Enemy positions, Enemy delays
        0, {0}, {0},                                      //numPatrollers, Patroller positions, Patroller offsets
        0, {0}, {0},                                      //numLava, Lava positions, Lava length
        0, {0}, {0}                                       //numWind, Wind positions, Wind directions
    },
    {   // Level 2
        5,
        4, {250, 250, 250, 250}, {0, 100, 200, 300},
        0, {0}, {0},
        4, {50, 100, 150, 200}, {40, 40, 40, 40},
        0, {0}, {0}
    },
    {   // Level 3
        1,
        5, {200, 205, 210, 215, 220}, {0, 10, 20, 30, 40},
        3, {150, 155, 160}, {0, 100, 200},
        2, {40, 200}, {30},
        3, {10, 20, 30}, {1, 1, 1}
    }
};


#endif //DUNGEONCRAWLER_LEVELS_H
