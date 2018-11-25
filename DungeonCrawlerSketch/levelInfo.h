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

    bool hasLavaFlow;
    
    int numEnemies;// = 0;
    int enemyPos[10];// = { 0 };
    int enemyDelay[10];// = { 0 };
    
    int numPatrollers;// = 0;
    int patrollerPos[10];// = { 0 };
    int patrollerOffset[10];// = { 0 };
    
    int numLava;// = 0;
    int lavaPos[5];// = { 0 };
    int lavaLength[5];// = { 0 };
    int lavaDelay[5];// = { 0 };
    
    int numWind;// = 0;
    int windPos[10];// = { 0 };
    int windDir[10];// = { 0 };
};


Level levels[NUMLEVELS] =
{
    {10, true, 1, {250}, {0}, 0, {0}, {0}, 0, {0}, {0}, {0}, 0, {0}, {0}},
    {20, false, 1, {250}, {0}, 1, {150}, {0}, 3, {150, 160, 170}, {10, 10, 10}, {0, 0, 0}, 2, {30, 40}, {1, 1}},
    {20, false, 5, {100, 105, 110, 115, 120}, {0, 10, 20, 30, 40}, 3, {150, 155, 160}, {0, 100, 200}, 2, {50, 90}, {30, 30}, {0, 40}, 4, {30, 40, 50, 60}, {1, 1, -1, -1}}
};


#endif //DUNGEONCRAWLER_LEVELS_H
