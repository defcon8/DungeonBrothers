/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>
#include "spriteslope.h"
#include "debug.h"

class cWorld;

class cSprite {
private:
    int iColorKeyR, iColorKeyG, iColorKeyB;
    char chTileSource[16];
    void fInit();
    Uint32 getPixelColor(SDL_Surface *surface, int x, int y);

    SDL_Surface* screen;
    cWorld* oWorld;
public:

    int iScrollOffset;
    void fLoad(const char *file);
    void fRender(int iCol, int iRow, int iDestX, int iDestY);

    void fSetSpriteWidth(int iPixels);
    void fSetSpriteHeight(int iPixels);
    void fSetSpriteWidthOffset(int iPixels);
    void fSetSpriteHeightOffset(int iPixels);
    void fSetSpriteSpacer(int iPixels);

    int iSpriteWidth, iSpriteHeight, iSpriteWidthOffset ,iSpriteHeightOffset, iSpriteSpacer;
    char* fGetTileSource();

    cSpriteSlope* oSlopeLeft, *oSlopeRight, *oSlopeTop, *oSlopeBottom;

    void fSetColorKey(int iR, int iG, int iB);
    void fScroll();
    bool fGetSlopes();

    cSprite(cWorld* oWorldRef);
    cSprite(cWorld* oWorldRef, SDL_Surface* sAlternativeScreen);

    ~cSprite();

    SDL_Surface* bitmap;

};
#endif /* SPRITE_H_ */
