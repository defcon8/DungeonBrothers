#include "bullit.h"

cBullit::cBullit(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef) : cLevelObject(screen, oLevelLayerRef, oCamRef, chTileSource, iSpriteHeight, iSpriteWidth)
{
    //ctor
}

cBullit::~cBullit()
{
    //dtor
}
