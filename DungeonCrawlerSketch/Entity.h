#ifndef ENTITY_H
#define ENTITY_H

#include "Pixel.h"
#include <Math.h>


class Entity {
public:
    inline Entity() = default;

    // mutators
    inline void setAnchorIndex( int index ) { anchor = index; };

    // accessors
    int getAnchorIndex( void ) const { return (int)round(anchor); };
    int getLeftBoundIndex( void ) const { return (int)round(anchor) - left_bound; };
    int getRightBoundIndex( void ) const { return (int)round(anchor) + right_bound; };
    int getLeftBound( void ) const { return left_bound; };
    int getRightBound( void ) const { return right_bound; };

    // functions
    virtual void updateEntity() = 0;
    virtual void drawEntity( CRGB board[], const int &blen ) = 0;

    double speed = 0;
    double anchor = 0;
    int left_bound = 0;
    int right_bound = 5;
};

#endif //ENTITY_H
