/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
/** \brief
 *
 * \param
 * \param
 * \return
 * Note: Do always set blOptimize to false when blIsBuffered is true.
 */

#include "spritelayer.h"
#include "world.h"
#include <cstring>
#include <fstream>

using namespace std;

SDL_Surface *spritelayerscreen;

void cSpriteLayer::fDrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B) {
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    switch (screen->format->BytesPerPixel) {
    case 1: { // 8-bpp
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
    }
    break;
    case 2: { // 15-bpp or 16-bpp
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
    }
    break;
    case 3: { // 24-bpp mode, usually not used
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN) {
            bufp[0] = color;
            bufp[1] = color >> 8;
            bufp[2] = color >> 16;
        } else {
            bufp[2] = color;
            bufp[1] = color >> 8;
            bufp[0] = color >> 16;
        }
    }
    break;
    case 4: { // 32-bpp
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
    }
    break;
    }
}


bool cSpriteLayer::fPixelIsTransparant(int iRow, int iCol, int iX, int iY, int iColCount){

    // Find out while tile this is.. in the sprite source.

    //Get the start TopLeft position.
    int iRowInSource = p_LevelData[iRow][iCol].iRow;
    int iColInSource = p_LevelData[iRow][iCol].iIndex;

    //Get the pixel
    int iPixelY = fRowToYInSpriteSheet(iRowInSource) + iY;
    int iPixelX = fColToXInSpriteSheet(iColInSource) + iX;

    bool solid = (bool)p_Source->p_PixelInfo[iPixelX][iPixelY].transparant;

    if(solid){
        fDrawPixel(oWorld->sScreenSurface,iX + (iColCount * oWorld->oLevelLayer->p_Source->iSpriteWidth),iY,0,255,0);
    }else{
        fDrawPixel(oWorld->sScreenSurface,iX + (iColCount * oWorld->oLevelLayer->p_Source->iSpriteWidth),iY,255,0,0);
    }

    Uint8 r, g, b; // temporary
    Uint32 iPixelColor = oWorld->oLevelLayer->p_Source->getPixelColor(oWorld->oLevelLayer->p_Source->bitmap,iPixelX,iPixelY);
    SDL_GetRGB(iPixelColor, oWorld->oLevelLayer->p_Source->bitmap->format, &r,&g,&b);

    fDrawPixel(oWorld->sScreenSurface,iX + (iColCount * oWorld->oLevelLayer->p_Source->iSpriteWidth),iY+32,r,g,b);

    TRACE("fPixelIsTransparant","Row: %d  Col: %d  RowInSource: %d  ColInSource: %d  PixelX: %d  PixelY: %d  iX: %d  iY: %d  Solid: %s", iRow, iCol, iRowInSource, iColInSource, iPixelX, iPixelY, iX ,iY, solid ? "true" : "false");

    return solid;

}

cSpriteLayer::cSpriteLayer(cWorld* oWorldRef, int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, bool blIsBuffered, bool blUseColorKey, int iKeyR, int iKeyG, int iKeyB) {
    oWorld = oWorldRef;

    /**< Initialize variables and setup data object holding the level data */
    fInitLayer(iRows, iCols, iSpriteHeightPX, iSpriteWidthPX, blOptimize, blIsBuffered);

    /**< Setup (source) object that contains the Sprite Sheet. */
    if(blBuffer) {
        sfBuffer = SDL_CreateRGBSurface(SDL_HWSURFACE,(iCols*iSpriteWidth),(iRows*iSpriteHeight),
                                        oWorld->sScreenSurface->format->BitsPerPixel,
                                        oWorld->sScreenSurface->format->Rmask,
                                        oWorld->sScreenSurface->format->Gmask,
                                        oWorld->sScreenSurface->format->Bmask,
                                        oWorld->sScreenSurface->format->Amask);

        p_Source = new cSprite(oWorld, sfBuffer);
    } else {
        p_Source = new cSprite(oWorld);
    }

    /**< Commmit the Color key for all surfaces. */
    if(blUseColorKey) {
        iColorKeyR = iKeyR;
        iColorKeyG = iKeyG;
        iColorKeyB = iKeyB;
        if(blBuffer) {
            SDL_SetColorKey(sfBuffer,SDL_SRCCOLORKEY, SDL_MapRGB(sfBuffer->format,  iColorKeyR,  iColorKeyG,  iColorKeyB));
        }
        p_Source->fSetColorKey(iColorKeyR,iColorKeyG,iColorKeyB);
    }

    /**< Fill map data with init data */
    fInitMap();
}

void cSpriteLayer::fGetSlopes() {
    p_Source->fGetSlopes();
}

void cSpriteLayer::fClear() {
    SDL_Rect rect;
    Uint32 color;
    if(blBuffer) {
        color = SDL_MapRGB (sfBuffer->format, 0, 0, 0);
        SDL_FillRect (sfBuffer, NULL, color);
    } else {
        color = SDL_MapRGB (oWorld->sScreenSurface->format, 0, 0, 0);
        SDL_FillRect (oWorld->sScreenSurface, NULL, color);
    }

}


void cSpriteLayer::fInitLayer(int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, bool blIsBuffered) {
    iSpriteHeight=iSpriteHeightPX;
    iSpriteWidth=iSpriteWidthPX;
    x=0;
    y=0;
    iRowCount=iRows;
    iColCount=iCols;
    iColorKeyR=0;
    iColorKeyG=0;
    iColorKeyB=0;
    blOptmizeLayer=blOptimize;
    blBuffer=blIsBuffered;

    //create data object
    p_LevelData = new sLevelBlock*[iRows];
    for(int i=0; i < iRows; i++)
        p_LevelData[i] = new sLevelBlock[iCols];
}

void cSpriteLayer::fSetSpriteHeight(int iPixels) {
    iSpriteHeight=iPixels;
}

int cSpriteLayer::fGetSpriteHeight() {
    return iSpriteHeight;
}

void cSpriteLayer::fSetSpriteWidth(int iPixels) {
    iSpriteWidth=iPixels;
}

int cSpriteLayer::fGetSpriteWidth() {
    return iSpriteWidth;
}

Uint8 cSpriteLayer::fReturnSpriteFlags(int iRow, int iCol) {
    return p_LevelData[iRow][iCol].iFlags;
}

void cSpriteLayer::fInitMap() {
    for (int iRow = 0; iRow < iRowCount; iRow++) {
        for (int iCol = 0; iCol < iColCount; iCol++) {
            p_LevelData[iRow][iCol].iIndex=1;
            p_LevelData[iRow][iCol].iRow=1;
            p_LevelData[iRow][iCol].iType=EMPTY;
            p_LevelData[iRow][iCol].iFlags=(unsigned char)~(PLATFORM | DAMAGE);
        }
    }
}

cSpriteLayer::~cSpriteLayer() {
    SDL_FreeSurface(spritelayerscreen);
    SDL_FreeSurface(sfBuffer);
}

SDL_Surface* cSpriteLayer::fRender(signed int CamX, signed int CamY) {
    // Don't draw things that are outside the view.
    int iStartCol=0;
    int iStartRow=0;
    int iEndCol=iColCount;
    int iEndRow=iRowCount;


    if(blOptmizeLayer) {
        iStartCol = fXToCol(-CamX);
        iEndCol = fXToCol((-CamX)+oWorld->oConfig->m_iScreenWidth);
        iStartRow = fYToRow(-CamY);
        iEndRow = fYToRow((-CamY)+oWorld->oConfig->m_iScreenHeight);

        // Protect drawing level outside its boundaries
        if(iStartCol<0) {
            iStartCol=0;
        }
        if(iStartRow<0) {
            iStartRow=0;
        }
        if(iEndCol>iColCount) {
            iEndCol=iColCount;
        }
        if(iEndRow>iRowCount) {
            iEndRow=iRowCount;
        }
    }

    // Loop
    for (int iRow = iStartRow; iRow < iEndRow; iRow++) {
        for (int iCol = iStartCol; iCol < iEndCol; iCol++) {
            if(p_LevelData[iRow][iCol].iType!=EMPTY)
                p_Source->fRender(p_LevelData[iRow][iCol].iIndex, p_LevelData[iRow][iCol].iRow, (fColToX(iCol)+CamX)+x, (fRowToY(iRow)+CamY)+y);
        }
    }

}

SDL_Surface* cSpriteLayer::fGetBufferSurface() {
    return sfBuffer;
}
int cSpriteLayer::fGetTotalRows() {
    return iRowCount;
}
int cSpriteLayer::fGetTotalCols() {
    return iColCount;
}

signed int cSpriteLayer::fColToXInSpriteSheet(signed int iCol) {
    return (iCol*(iSpriteWidth+p_Source->iSpriteSpacer)) +p_Source->iSpriteSpacer; // See below
}
signed int cSpriteLayer::fRowToYInSpriteSheet(signed int iRow) {
    TRACE("fPixelIsTransparant","iSpriteHeightOffset: %d",p_Source->iSpriteHeightOffset);
    return p_Source->iSpriteHeightOffset + (iRow*(p_Source->iSpriteHeight+p_Source->iSpriteSpacer)); //TODO: The last value (iSpriteSpace isnt correct, it should be heightoffset, but somehow it doesnt work)
}

signed int cSpriteLayer::fColToX(signed int iCol) {
    return (iCol*iSpriteWidth);
}
signed int cSpriteLayer::fRowToY(signed int iRow) {
    return (iRow*iSpriteHeight);
}
signed int cSpriteLayer::fXToCol(signed int iWidth) {
    return (iWidth/iSpriteWidth);
}
signed int cSpriteLayer::fYToRow(signed int iHeight) {
    return (iHeight/iSpriteHeight);
}
signed int cSpriteLayer::fGetWidth() {
    return iColCount * iSpriteWidth;
}
signed int cSpriteLayer::fGetHeight() {
    return iRowCount * iSpriteHeight;
}
bool cSpriteLayer::fIsBuffered() {
    return blBuffer;
}
