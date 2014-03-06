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
#include "world.h"

bool cSprite::fGetSlopes() {
    //Create Slope from edges
    //oSlopeLeft = new cSpriteSlope(iSpriteHeight);
    //oSlopeRight = new cSpriteSlope(iSpriteHeight);
    //oSlopeTop = new cSpriteSlope(iSpriteWidth);
    //oSlopeBottom = new cSpriteSlope(iSpriteWidth);

    int iMaxCols = ((bitmap->w-iSpriteWidthOffset) / (iSpriteSpacer+iSpriteWidth));
    int iMaxRows = ((bitmap->h-iSpriteHeightOffset) / (iSpriteSpacer+iSpriteHeight));


    for(int iCol=0; iCol<=iMaxCols; iCol++) {
        for(int iRow=0; iRow<=iMaxRows; iRow++) {
            int iStartX = iSpriteWidthOffset+(iSpriteSpacer*(iCol+1))+(iCol*iSpriteWidth);
            int iStartY = iSpriteHeightOffset+(iSpriteSpacer*(iRow+1))+(iRow*iSpriteHeight);

            //Scan Top
            for(int iScanX=0; iScanX<=iSpriteWidth; iScanX++) {
                for(int iScanY=iStartY; iScanY<=iStartY+iSpriteHeight; iScanY++) {
                    // jaaaaaaaaaaaaaaaaaaaaaaaaaa hier gaat hij dus mooi kapott!!!!!!!!
                    //unsigned int pixelcolor = fGetPixel(bitmap,iScanX,iScanY);
                    //debug
                    //end debug
                }
            }

        }
    }
}

void cSprite::fLoad(const char *file) {
    bitmap = SDL_DisplayFormatAlpha(SDL_LoadBMP(file));
    SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, SDL_MapRGB(bitmap->format,  iColorKeyR,  iColorKeyG,  iColorKeyB));
    //Store the filename localy in chTileSource, we need it later when saving level to disk.
    memcpy(&chTileSource[0],file,16);

}

char* cSprite::fGetTileSource() {
    return &chTileSource[0];
}

void cSprite::fSetColorKey(int iR, int iG, int iB) {
    iColorKeyR = iR;
    iColorKeyG = iG;
    iColorKeyB = iB;
}

void cSprite::fRender(int iCol, int iRow, int iDestX, int iDestY) {
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

    SDL_BlitSurface(bitmap, &source, screen, &destination);
}

cSprite::cSprite(cWorld* oWorldRef) {
    oWorld = oWorldRef;
    screen = oWorld->sScreenSurface;
    fInit();
}

cSprite::cSprite(cWorld* oWorldRef, SDL_Surface* sAlternativeScreen) {
    oWorld = oWorldRef;
    screen = sAlternativeScreen;
    fInit();
}


cSprite::~cSprite() {
    SDL_FreeSurface(bitmap);
}

void cSprite::fInit() {
    iSpriteSpacer=0;
    iSpriteHeight=0;
    iSpriteWidth=0;
    iSpriteHeightOffset=0;
    iSpriteWidthOffset=0;
    iScrollOffset=0;
}
