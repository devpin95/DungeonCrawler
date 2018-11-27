#ifndef FINAL_LEVEL_H
#define FINAL_LEVEL_H

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
    int windPos[5];// = { 0 };
    int windDir[5];// = { 0 };
};

#endif //FINAL_LEVEL_H
