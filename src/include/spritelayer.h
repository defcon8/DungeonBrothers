/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
/** Spritelayer: draws a set of sprite's on a SDL Surface.
 *
 * Optmalisation:   When this is True things outside the viewport doesnt get drawed onto the screen surface,
 *                  this gives a performance boost.
 * Buffered:
 *                  false:
 *                  Draw the layer directly onto the main screen on each fRender() call. fRender() should be
 *                  called each frame update.
 *
 *                  true:
 *                  Render the layer on to the buffer surface when 'once' fRender is called. Then you
 *                  can retreive the prerendered layer by using fGetBufferSurface().
 *
 */

#ifndef SPRITELAYER_H_
#define SPRITELAYER_H_

#include "sprite.h"

class cWorld;

class cSpriteLayer {
    //Sprite Types
#define EMPTY 0
#define SPRITE  1

    //Sprite Flags
#define WALL 1
#define ENEMYWALL 2
#define PLATFORM 4
#define USELIGHT 8
#define OVERLAP 16
#define ANBACK 32
#define ANFRONT 64
#define WATER 128
#define DAMAGE 256
#define CONVL 512
#define CONVR 1024
#define TURN 2048
#define DESTROYABLE 4096

private:
    struct slevelblock {
        Uint8 source;
        Uint8 row;
        Uint8 index;
        Uint8 type;
        Uint8 animations;
        Uint8 aniframestep;
        Uint8 collide;
        Uint8 flags;

    };

    //Local Members
    cWorld* world;

    int spritewidth, spriteheight;
    int rowcount, colcount;
    bool optmizelayer;
    bool usebuffer;
    bool usecolorkey;
    int colorkeyr, colorkeyg, colorkeyb;

    //Methods
    void initMap();
    void drawPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b);
    void initLayer(int rows, int cols, int spriteheight, int spritewidth, bool optimize, bool isbuffered);

public:
    cSpriteLayer(cWorld* _world, int rows, int cols, int spriteheight, int spritewidth, bool optimize, bool isbuffered, bool usecolorkey, int keyr, int keyg, int keyb); /**< Constructor to render directly to main screen */
    ~cSpriteLayer();

    //Data Objects
    cSprite *source;
    SDL_Surface* render(signed int camx, signed int camy);
    SDL_Surface* buffer;
    slevelblock **leveldata;

    //Members
    int x,y;

    //Methods
    Uint8 returnSpriteFlags(int row, int col);
    void setSpriteWidth(int pixels);
    void getSlopes();
    int getSpriteWidth();
    void setSpriteHeight(int pixels);
    void clearlayer();
    int getSpriteHeight();
    bool pixelIsTransparant(int row, int col, int x, int y, int colcount);
    int getTotalRows();
    int getTotalCols();
    int getWidth();
    int getHeight();
    signed int colToXInSpriteSheet(signed int col);
    signed int rowToYInSpriteSheet(signed int row);
    int xToCol(signed int width);         /**< Returns the col number of the given width in pixels */
    int yToRow(signed int height);       /**< Returns the row number of the given height in pixels */
    int colToX(signed int col);           /**< Returns the width in pixels of the col number */
    int rowToY(signed int row);          /**< Returns the height in pixels of the row number */
    bool isBuffered();                         /**< Returns if the surface is a buffered or not. */
    SDL_Surface* getBufferSurface();           /**< Returns the buffer surface. */
};

#endif /* SPRITELAYER_H_ */
