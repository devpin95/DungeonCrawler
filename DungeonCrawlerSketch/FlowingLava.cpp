#include "FlowingLava.h"

FlowingLava::FlowingLava() {
    anchor = 0;
    flowhead = 1;
    p.R = 255;
    p.G = 69;
    p.B = 0;
}

void FlowingLava::updateEntity() {
    ++counter;

    if ( counter == LAVA_FLOW_RATE ) {
        if ( flowhead != 300 ) {
            ++flowhead;
        }
        counter = 0;
    }
}

void FlowingLava::drawEntity( CRGB board[], const int &blen ) {
    for ( int i = 0; i < flowhead; ++ i ) {
        board[ i ] = CRGB( p.R, p.G, p.B );
    }
}
