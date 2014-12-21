#ifndef BULLIT_H
#define BULLIT_H
#include "levelobject.h"

using namespace std;

class cWorld;

class cBullit : public cLevelObject {
private:
    float scalex, scaley;
    float velocityx, velocityy;
    int angle, speed;
public:
    cBullit(cWorld* world, const char* tilesource, int spriteheight, int spritewidth, int angleref, int speedref);
    ~cBullit();
    void aI();
};

#endif // PLAYER_H

