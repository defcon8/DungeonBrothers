#include "sprite.h"


 
void cSprite::fLoad(const char *file)
{
    bitmap = SDL_LoadBMP(file);
    SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format,  iColorKeyR,  iColorKeyG,  iColorKeyB));
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

void cSprite::fScroll(int iPixelOffset)
{
   iScrollOffset=iPixelOffset;  
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
    SDL_Rect destination;destination.x = iDestX;
    destination.y = iDestY;
    destination.w = iSpriteWidth;
    destination.h = iSpriteHeight; 
    
    SDL_BlitSurface(bitmap, &source, spritescreen, &destination);
}

cSprite::cSprite(SDL_Surface *screen)
{
      spritescreen = screen;
      iSpriteSpacer=0;
      iSpriteHeight=0;
      iSpriteWidth=0;
      iSpriteHeightOffset=0;
      iSpriteWidthOffset=0;
}

cSprite::~cSprite()
{
     SDL_FreeSurface(bitmap);
}
