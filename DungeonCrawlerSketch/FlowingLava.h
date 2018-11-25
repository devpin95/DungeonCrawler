#ifndef FINAL_FLOWINGLAVA_H
#define FINAL_FLOWINGLAVA_H

#include <FastLED.h>
//#include "globals.h"
#include "Entity.h"

#define LAVA_FLOW_RATE 30

class FlowingLava : public Entity {
public:
    FlowingLava();
    void updateEntity();
    void drawEntity( CRGB board[], const int &blen );

    Pixel p;

    int flowhead = 1;
    int counter = 0;
};


#endif //FINAL_FLOWINGLAVA_H
