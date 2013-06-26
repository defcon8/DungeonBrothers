#ifndef BULLIT_H
#define BULLIT_H
#include "levelobject.h"

class cWorld;

class cBullit : public cLevelObject
{
    public:
        cBullit(cWorld* oWorldRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth);
        ~cBullit();
    protected:
    private:
};

#endif // BULLIT_H
