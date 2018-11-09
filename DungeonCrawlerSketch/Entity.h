#ifndef ENTITY_H
#define ENTITY_H

#include "Pixel.h"

class Entity {
public:
    inline Entity() = default;
    inline void setSpd( int s ) { speed = s; };

    // mutators
    inline void setAnchorIndex( int index ) { anchor = index; };

    // accessors
    int getAnchorIndex( void ) const { return anchor; };
    int getLeftBoundIndex( void ) const { return anchor - left_bound; };
    int getRightBoundIndex( void ) const { return anchor + right_bound; };
    int getLeftBound( void ) const { return left_bound; };
    int getRightBound( void ) const { return right_bound; };

    // functions
    virtual void updateEntity() = 0;
    virtual void drawEntity() = 0;
protected:
    int speed = 0;
    int anchor = 0;
    int left_bound = 0;
    int right_bound = 5;
};

#endif //ENTITY_H
