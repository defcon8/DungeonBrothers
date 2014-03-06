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
    struct sLevelBlock {
        Uint8 bySource;
        Uint8 iRow;
        Uint8 iIndex;
        Uint8 iType;
        Uint8 iAnimations;
        Uint8 AniFrameStep;
        Uint8 blCollide;
        Uint8 iFlags;
    };

    //Local Members
    cWorld* oWorld;

    int iSpriteWidth, iSpriteHeight;
    int iRowCount, iColCount;
    bool blOptmizeLayer;
    bool blBuffer;
    bool blUseColorKey;
    int iColorKeyR, iColorKeyG, iColorKeyB;

    //Methods
    void fInitMap();
    void fInitLayer(int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, bool blIsBuffered);

public:
    cSpriteLayer(cWorld* oWorldRef, int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, bool blIsBuffered, bool blUseColorKey, int iKeyR, int iKeyG, int iKeyB); /**< Constructor to render directly to main screen */
    ~cSpriteLayer();

    //Data Objects
    cSprite *p_Source;
    SDL_Surface* fRender(signed int CamX, signed int CamY);
    SDL_Surface* sfBuffer;
    sLevelBlock **p_LevelData;

    //Members
    int x,y;

    //Methods
    Uint8 fReturnSpriteFlags(int iRow, int iCol);
    void fSetSpriteWidth(int iPixels);
    void fGetSlopes();
    int fGetSpriteWidth();
    void fSetSpriteHeight(int iPixels);
    void fClear();
    int fGetSpriteHeight();
    int fGetTotalRows();
    int fGetTotalCols();
    int fGetWidth();
    int fGetHeight();
    int fWidthToCol(signed int iWidth);         /**< Returns the col number of the given width in pixels */
    int fHeightToRow(signed int iHeight);       /**< Returns the row number of the given height in pixels */
    int fColToWidth(signed int iCol);           /**< Returns the width in pixels of the col number */
    int fRowToHeight(signed int iRow);          /**< Returns the height in pixels of the row number */
    bool fIsBuffered();                         /**< Returns if the surface is a buffered or not. */
    SDL_Surface* fGetBufferSurface();           /**< Returns the buffer surface. */
};

#endif /* SPRITELAYER_H_ */
