#include "bullit.h"
#include "world.h"

cBullit::cBullit(cWorld* oWorldRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth) : cLevelObject(cWorld* oWorldRef, chTileSource, iSpriteHeight, iSpriteWidth)
{
    //ctor
}

cBullit::~cBullit()
{
    //dtor
}
