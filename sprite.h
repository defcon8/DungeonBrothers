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
    int colorkeyr, colorkeyg, colorkeyb;
    char tilesource[16];
    void init();

    SDL_Surface* screen;
    cWorld* world;

    struct spixelinfo{
        int transparant;
    };

public:


    spixelinfo **pixelinfo;

    Uint32 getPixelColor(SDL_Surface *surface, int x, int y);
    int scrolloffset;
    void load(const char *file);
    void render(int col, int row, int destx, int desty);

    void setSpriteWidth(int pixels);
    void setSpriteHeight(int pixels);
    void setSpriteWidthOffset(int pixels);
    void setSpriteHeightOffset(int pixels);
    void setSpriteSpacer(int pixels);

    int spritewidth, spriteheight, spritewidthoffset ,spriteheightoffset, spritespacer;
    char* getTileSource();

    cSpriteSlope* slopeleft, *sloperight, *slopetop, *slopebottom;

    void setColorKey(int r, int g, int b);
    void scroll();
    bool getSlopes();

    cSprite(cWorld* _world);
    cSprite(cWorld* _world, SDL_Surface* alternativescreen);

    ~cSprite();

    SDL_Surface* bitmap;

};
#endif /* SPRITE_H_ */
