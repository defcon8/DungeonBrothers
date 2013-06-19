/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "sprite.h"
#include <cstring>

void cSprite::fLoad(const char *file)
{
    bitmap = SDL_DisplayFormatAlpha(SDL_LoadBMP(file));
    SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format,  iColorKeyR,  iColorKeyG,  iColorKeyB));

    //Store local, we need it later when saving level to disk.
    memcpy(&chTileSource[0],file,16);
}

char* cSprite::fGetTileSource()
{
    return &chTileSource[0];
}

void cSprite::fSetColorKey(int iR, int iG, int iB)
{
    iColorKeyR = iR;
    iColorKeyG = iG;
    iColorKeyB = iB;
}

void cSprite::fSetSpriteSpacer(int iPixels)
{
    iSpriteSpacer=iPixels;
}

void cSprite::fSetSpriteWidth(int iPixels)
{
    iSpriteWidth=iPixels;
}

void cSprite::fSetSpriteHeight(int iPixels)
{
    iSpriteHeight=iPixels;
}

void cSprite::fSetSpriteWidthOffset(int iPixels)
{
    iSpriteWidthOffset=iPixels;
}

void cSprite::fSetSpriteHeightOffset(int iPixels)
{
    iSpriteHeightOffset=iPixels;
}

int cSprite::fGetSpriteSpacer()
{
    return iSpriteSpacer;
}

int cSprite::fGetSpriteWidth()
{
    return iSpriteWidth;
}

int cSprite::fGetSpriteHeight()
{
    return iSpriteHeight;
}

int cSprite::fGetSpriteWidthOffset()
{
    return iSpriteWidthOffset;
}

int cSprite::fGetSpriteHeightOffset()
{
    return iSpriteHeightOffset;
}

void cSprite::fScroll()
{
    if((iScrollOffset+iScreenWidth)==iSpriteWidth)
    {
        iScrollOffset=0;
    }
    else
    {
        iScrollOffset++;
    }
}

void cSprite::fRender(int iCol, int iRow, int iDestX, int iDestY)
{
    // Part of the bitmap that we want to draw
    SDL_Rect source;
    source.x = iSpriteWidthOffset+(iSpriteSpacer*(iCol+1))+(iCol*iSpriteWidth);
    source.y = iSpriteHeightOffset+(iSpriteSpacer*(iRow+1))+(iRow*iSpriteHeight);
    source.w = iSpriteWidth;
    source.h = iSpriteHeight;

    // Part of the screen we want to draw the sprite to
    SDL_Rect destination;
    destination.x = iDestX-iScrollOffset;
    destination.y = iDestY;
    destination.w = iSpriteWidth;
    destination.h = iSpriteHeight;

    SDL_BlitSurface(bitmap, &source, spritescreen, &destination);
}

cSprite::cSprite(SDL_Surface *screen, int iScreenWidthRef, int iScreenHeightRef)
{
    spritescreen = screen;
    iSpriteSpacer=0;
    iSpriteHeight=0;
    iSpriteWidth=0;
    iSpriteHeightOffset=0;
    iSpriteWidthOffset=0;
    iScrollOffset=0;
    iScreenWidth=iScreenWidthRef;
    iScreenHeight=iScreenHeightRef;
}

cSprite::~cSprite()
{
    SDL_FreeSurface(bitmap);
}
