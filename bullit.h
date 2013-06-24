#ifndef BULLIT_H
#define BULLIT_H
#include "levelobject.h"


class cBullit : public cLevelObject
{
    public:
        cBullit(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef);
        ~cBullit();
    protected:
    private:
};

#endif // BULLIT_H
