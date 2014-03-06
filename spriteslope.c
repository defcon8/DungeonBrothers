#include "spriteslope.h"

cSpriteSlope::cSpriteSlope(int iAmount) {
    //ctor

    // TODO (Bastiaan#1#): int needs to be a 8 bit int, this object is created many times. So keeping it small is best. At this time i cant find the UINT8 datatype.

    // Initialise data object
    p_SlopeValue = new int*[iAmount];
    for(int i=0; i < iAmount; i++)
        p_SlopeValue[i] = 0;
}

cSpriteSlope::~cSpriteSlope() {
    //dtor
}
