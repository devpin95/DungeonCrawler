#ifndef DUNGEONCRAWLER_UTILITYFUNCTIONS_H
#define DUNGEONCRAWLER_UTILITYFUNCTIONS_H

/*
 * 1:
 * Clear the vectors (enemy, patroller, lava, wind)
 *
 * 2:
 * Add all entities that we need from the JSON object
 * 
 * 3:
 * Set player position
 */


void setupLevel(const int& levelNum)
{    
  char json[] = "{\"num\":2,\"levels\":[{\"ppos\":0,\"Enemies\":{\"num\":1,\"pos\":[250],\"delay\":[0]},\"Patrollers\":{\"num\":0},\"Lava\":{\"num\":0},\"Wind\":{\"num\":0}},{\"ppos\\\":20,\"Enemies\\\":{\"num\\\":1,\"pos\":[250],\"delay\":[0]},\"Patrollers\":{\"num\":1,\"pos\":[150]},\"Lava\":{\"num\":1,\"pos\":[150]},\"Wind\":{\"num\":2,\"pos\":[30,40],\"mul\":[1,1]}}]}";

  //JSON Stuff
  const size_t bufferSize = 6*JSON_ARRAY_SIZE(1) + 3*JSON_ARRAY_SIZE(2) + 3*JSON_OBJECT_SIZE(1) + 3*JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(3) + 2*JSON_OBJECT_SIZE(5) + 200;
  StaticJsonBuffer<bufferSize> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
   if (!root.success())
    {
      Serial.println("FAIL");
    }
    //PLAYER POSITION
    /*player.anchor = levels[levelNum].playerPos;
    
    //CLEAR ALL VECTORS
//    enemy.clear();
//    patroller.clear();
//    lava.clear();
//    wind.clear();

    //ADDING REQUIRED ENTITIES
    for (int i = 0; i < levels[levelNum].numEnemies; ++i)//ENEMIES
    {
      enemy[i].anchor = levels[levelNum].enemyPos[i];
//      enemyPool[i].anchor = levels[levelNum].enemyPos[i];
//      enemy.push_back( enemyPool[i] );
    }
    for (int i = 0; i < levels[levelNum].numPatrollers; ++i)
    {
      patroller[i].anchor = levels[levelNum].patrollerPos[i];
//      patrollerPool[i].anchor = levels[levelNum].patrollerPos[i];
//      patroller.push_back( patrollerPool[i] );
    }
    for (int i = 0; i < levels[levelNum].numLava; ++i)
    {
      lava[i].anchor = levels[levelNum].lavaPos[i];
//      lavaPool[i].anchor = levels[levelNum].lavaPos[i];
//      lava.push_back( lavaPool[i] );
    }
    for (int i = 0; i < levels[levelNum].numWind; ++i)
    {
      wind[i].anchor = levels[levelNum].windPos[i];
      wind[i].multiplier = levels[levelNum].windDir[i] * 0.5;
//      windPool[i].anchor = levels[levelNum].windPos[i];
//      windPool[i].multiplier = levels[levelNum].windDir[i] * 0.5;
//      wind.push_back( windPool[i] );
    }*/

  
    int temp, temp2;
    
    //clear all vectors
//    enemy.clear();
//    patroller.clear();
//    lava.clear();
//    wind.clear();

    //ADDING REQUIRED ENTITIES (JSON)
    for (int i = 0; i < root["levels"][levelNum]["Enemies"]["num"]; ++i)//ENEMIES
    {
        temp = root["levels"][levelNum]["Enemies"]["pos"][i];
        enemy[i].anchor = temp;
    }
    for (int i = 0; i < root["levels"][levelNum]["Patrollers"]["num"]; ++i)//PATROLLERS
    {
        temp = root["levels"][levelNum]["Patrollers"]["pos"][i];
        patroller[i].anchor = temp;
    }
    for (int i = 0; i < root["levels"][levelNum]["Lava"]["num"]; ++i)//LAVA
    {
        temp = root["levels"][levelNum]["Lava"]["pos"][i];
        lava[i].anchor = temp;
    }
    for (int i = 0; i < root["levels"][levelNum]["Wind"]["num"]; ++i)//WIND
    {
        temp = root["levels"][levelNum]["Wind"]["pos"][i];
        temp2 = root["levels"][levelNum]["Wind"]["mul"][i];
        wind[i].anchor = temp;
        wind[i].multiplier = temp * 0.5;
    }

    //SET PLAYER POSITION
    temp = root["levels"][levelNum]["ppos"];
    player.anchor = temp;
}


#endif //DUNGEONCRAWLER_UTILITYFUNCTIONS_H
