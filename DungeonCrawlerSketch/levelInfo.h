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
    //int enemyDelay[20] = { 0 };
    
    int numPatrollers;// = 0;
    int patrollerPos[20];// = { 0 };
    //int patrollerOffset[20] = { 0 };
    
    int numLava;// = 0;
    int lavaPos[20];// = { 0 };
    //int lavaSize[20] = { 0 };
    //int lavaDelay[20] = { 0 };
    
    int numWind;// = 0;
    int windPos[20];// = { 0 };
    int windDir[20];// = { 0 };
};


Level levels[2] = 
{
   { 1,    2, {220, 240},               0, {0},     0, {0},     0, {0}, {0} },
   { 1,    4, {160, 180, 220, 240},     0, {0},     0, {0},     0, {0}, {0} }
};


#endif //DUNGEONCRAWLER_LEVELS_H
