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

class cSprite
{
private:
    int iSpriteWidth, iSpriteHeight, iSpriteWidthOffset ,iSpriteHeightOffset, iSpriteSpacer;
    int iColorKeyR, iColorKeyG, iColorKeyB;
    char chTileSource[16];

    SDL_Surface* bitmap;
    SDL_Surface *spritescreen;
public:
    int iScrollOffset;
    void fLoad(const char *file);
    void fRender(int iCol, int iRow, int iDestX, int iDestY);

    void fSetSpriteWidth(int iPixels);
    void fSetSpriteHeight(int iPixels);
    void fSetSpriteWidthOffset(int iPixels);
    void fSetSpriteHeightOffset(int iPixels);
    void fSetSpriteSpacer(int iPixels);

    int fGetSpriteWidth();
    int fGetSpriteHeight();
    int fGetSpriteWidthOffset();
    int fGetSpriteHeightOffset();
    int fGetSpriteSpacer();

    char* fGetTileSource();

    void fSetColorKey(int iR, int iG, int iB);
    void fScroll();

    cSprite(SDL_Surface *screen);
    ~cSprite();
};
#endif /* SPRITE_H_ */
