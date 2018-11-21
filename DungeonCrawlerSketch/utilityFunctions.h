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
    int temp, temp2;
    
    //clear all vectors
    enemy.clear();
    patroller.clear();
    lava.clear();
    wind.clear();

    //ADDING REQUIRED ENTITIES
    for (int i = 0; i < root["levels"][levelNum]["Enemies"]["num"]; ++i)//ENEMIES
    {
        temp = root["levels"][levelNum]["Enemies"]["pos"][i];
        enemy.push_back( Enemy(temp) );
    }
    for (int i = 0; i < root["levels"][levelNum]["Patrollers"]["num"]; ++i)//PATROLLERS
    {
        temp = root["levels"][levelNum]["Patrollers"]["pos"][i];
        patroller.push_back( Patroller(temp) );
    }
    for (int i = 0; i < root["levels"][levelNum]["Lava"]["num"]; ++i)//LAVA
    {
        temp = root["levels"][levelNum]["Lava"]["pos"][i];
        lava.push_back( Lava(temp) );
    }
    for (int i = 0; i < root["levels"][levelNum]["Wind"]["num"]; ++i)//WIND
    {
        temp = root["levels"][levelNum]["Wind"]["pos"][i];
        temp2 = root["levels"][levelNum]["Wind"]["mul"][i];
        wind.push_back( Wind(temp, temp2) );
    }

    //SET PLAYER POSITION
    temp = root["levels"][levelNum]["ppos"];
    player.anchor = temp;
}


#endif //DUNGEONCRAWLER_UTILITYFUNCTIONS_H
