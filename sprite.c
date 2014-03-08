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

Uint32 cSprite::getPixelColor(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

bool cSprite::fGetSlopes() {
    //Create Slope from edges
    //oSlopeLeft = new cSpriteSlope(iSpriteHeight);
    //oSlopeRight = new cSpriteSlope(iSpriteHeight);
    //oSlopeTop = new cSpriteSlope(iSpriteWidth);
    //oSlopeBottom = new cSpriteSlope(iSpriteWidth);

    int iMaxCols = ((bitmap->w-iSpriteWidthOffset) / (iSpriteSpacer+iSpriteWidth))-1; //Todo: I had to add -1 here but i doubt this is correct..anyway it works now..
    int iMaxRows = ((bitmap->h-iSpriteHeightOffset) / (iSpriteSpacer+iSpriteHeight))-1;

    TRACE("Slopes","Columns: %d", iMaxCols);
    TRACE("Slopes","Rows: %d", iMaxRows);

    int iPixelCount=0;

    for(int iCol=0; iCol<=iMaxCols; iCol++) {
        for(int iRow=0; iRow<=iMaxRows; iRow++) {
            int iStartX = iSpriteWidthOffset+(iSpriteSpacer*(iCol+1))+(iCol*iSpriteWidth);
            int iStartY = iSpriteHeightOffset+(iSpriteSpacer*(iRow+1))+(iRow*iSpriteHeight);

            //Scan Top
            for(int iScanY=iStartY; iScanY<=iStartY+iSpriteHeight; iScanY++) {
                long lSlopeRow; // The long containing the row information.. long is 32 bit.. each bit tells if the the pixel is transparant or not..
                for(int iScanX=iStartX; iScanX<=iStartX+iSpriteWidth; iScanX++) {
                    Uint8 r, g, b;
                    SDL_LockSurface(bitmap);
                    Uint32 iPixelColor = getPixelColor(bitmap,iScanX,iScanY);
                    SDL_GetRGB(iPixelColor, bitmap->format, &r,&g,&b);
                    SDL_UnlockSurface(bitmap);
                    // The position of the bit in the Long (lSlopeRow) is the same as the pixel position in the row to be scanned
                    if((r==iColorKeyR) && (g==iColorKeyG) && (b==iColorKeyB)) {
                        //Transparant Pixel (air...)
                        lSlopeRow &= ~(1 << (iScanX-iStartX)); //clear the bit
                    } else {
                        //Object (floor, wall, ground whatever..) we can stand on it
                        lSlopeRow |= 1 << (iScanX-iStartX); //set the bit
                    }
                    iPixelCount++;
                }
            }
        }
    }
    TRACE("Slopes","Pixels analyzed: %d", iPixelCount);
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
