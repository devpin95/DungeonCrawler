#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#define PLAYER_LENGTH 5

class Player : public Entity {
public:
    Player();
    void updateEntity();
    void drawEntity();
private:
    Pixel pixels[PLAYER_LENGTH];
};


#endif //DUNGEONCRAWLER_PLAYER_H
