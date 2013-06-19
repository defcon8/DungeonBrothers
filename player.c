#include "player.h"

cPlayer::cPlayer(SDL_Surface* screen, cSpriteLayer* oLevelLayerRef, cCamera* oCamRef, char* chTileSource, int iSpriteHeight, int iSpriteWidth, int iScreenWidthRef, int iScreenHeightRef) : cLevelObject(screen, oLevelLayerRef, oCamRef, chTileSource, iSpriteHeight, iSpriteWidth, iScreenWidthRef, iScreenHeightRef)
{
}

cPlayer::~cPlayer()
{
}

void cPlayer::fAI()
{
    oPlayerLayer->x++;
}
