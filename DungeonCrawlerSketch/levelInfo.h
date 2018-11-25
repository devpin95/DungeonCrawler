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
    {10, false, 4, {250, 250, 250, 250}, {0, 50, 100, 150}, 0, {0}, {0}, 0, {0}, {0}, {0}, 0, {0}, {0}},
    {10, false, 8, {250, 250, 250, 250, 250, 250, 250, 250}, {0, 5, 10, 15, 100, 105, 110, 115}, 0, {0}, {0}, 0, {0}, {0}, {0}, 0, {0}, {0}},
    {10, false, 6, {200, 250, 200, 250, 200, 250}, {0, 0, 50, 50, 100, 100}, 2, {50, 120}, {0, 100}, 0, {0}, {0}, {0}, 0, {0}, {0}},
    {10, false, 2, {250, 280}, {0, 0}, 4, {20, 50, 150, 180}, {0, 50, 100, 150}, 0, {0}, {0}, {0}, 2, {125, 145}, {1, 1}},
    {10, true, 0, {0}, {0}, 0, {0}, {0}, 0, {0}, {0}, {0}, 4, {40, 100, 160, 220}, {-1, -1, -1, -1}},
    {10, false, 0, {0}, {0}, 6, {30, 80, 130, 180, 230, 280}, {0, 10, 20, 30, 40, 50}, 3, {20, 120, 220}, {40, 40, 40}, {0, 50, 100}, 0, {0}, {0}},
    {15, false, 9, {100, 100, 100, 220, 220, 220, 200, 200, 200}, {0, 10, 20, 100, 110, 120, 150, 160, 170}, 0, {0}, {0}, 4, {0, 100, 130, 160}, {10, 10, 30, 30}, {0, 100, 100, 200}, 1, {110}, {1}},
    {15, false, 9, {100, 100, 100, 220, 220, 220, 200, 200, 200}, {0, 10, 20, 100, 110, 120, 150, 160, 170}, 0, {0}, {0}, 4, {0, 100, 130, 160}, {10, 10, 30, 30}, {0, 100, 100, 200}, 1, {110}, {1}}
};


#endif //DUNGEONCRAWLER_LEVELS_H
