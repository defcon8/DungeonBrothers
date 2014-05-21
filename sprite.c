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

    // This function scans all tiles in the bitmap and detects if a pixel is transparant or not. Information for each pixel row of the sprite is stored in so
    // called slopes which is basicaly a word (32 bit). Each bit in the word tells if the pixels is transparant or not.

    //create data object
    p_PixelInfo = new sPixelInfo*[bitmap->w];
    for(int i=0; i < bitmap->w; i++)
        p_PixelInfo[i] = new sPixelInfo[bitmap->h];

    int iPixelCount=0; // just for debugging purposes, count how many pixels are analyzed

    SDL_LockSurface(bitmap);
    for(int iX=0; iX<=bitmap->w-1; iX++) {
        for(int iY=0; iY<=bitmap->h-1; iY++) {

                    Uint8 r, g, b; // temporary
                    Uint32 iPixelColor = getPixelColor(bitmap,iX,iY);
                    SDL_GetRGB(iPixelColor, bitmap->format, &r,&g,&b);

                    // The position of the bit in the Long (lSlopeRow) is the same as the pixel position in the row to be scanned
                    if((r==iColorKeyR) && (g==iColorKeyG) && (b==iColorKeyB)) { // if the color is the keycolor then it it transparant...
                        //Transparant Pixel (air...)
                        p_PixelInfo[iX][iY].transparant = 0;
                    } else {
                        //Object (floor, wall, ground whatever..) we can stand on it
                        p_PixelInfo[iX][iY].transparant = 1;
                    }

                    iPixelCount++;
        }
    }
    SDL_UnlockSurface(bitmap);

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
    source.x = iSpriteWidthOffset+(iCol*(iSpriteWidth+iSpriteSpacer));
    source.y = iSpriteHeightOffset+(iRow*(iSpriteHeight+iSpriteSpacer));
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
