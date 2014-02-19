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

cSpriteLayer::cSpriteLayer(cWorld* oWorldRef, int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, bool blIsBuffered, bool blUseColorKey, int iKeyR, int iKeyG, int iKeyB)
{
    oWorld = oWorldRef;

    /**< Initialize variables and setup data object holding the level data */
    fInitLayer(iRows, iCols, iSpriteHeightPX, iSpriteWidthPX, blOptimize, blIsBuffered);

    /**< Setup (source) object that contains the Sprite Sheet. */
    if(blBuffer)
    {
        sfBuffer = SDL_CreateRGBSurface(SDL_HWSURFACE,(iCols*iSpriteWidth),(iRows*iSpriteHeight),
                                        oWorld->sScreenSurface->format->BitsPerPixel,
                                        oWorld->sScreenSurface->format->Rmask,
                                        oWorld->sScreenSurface->format->Gmask,
                                        oWorld->sScreenSurface->format->Bmask,
                                        oWorld->sScreenSurface->format->Amask);

        p_Source = new cSprite(oWorld, sfBuffer);
    }
    else
    {
        p_Source = new cSprite(oWorld);
    }

    /**< Commmit the Color key for all surfaces. */
    if(blUseColorKey)
    {
        iColorKeyR = iKeyR;
        iColorKeyG = iKeyG;
        iColorKeyB = iKeyB;
        if(blBuffer){
            SDL_SetColorKey(sfBuffer,SDL_SRCCOLORKEY, SDL_MapRGB(sfBuffer->format,  iColorKeyR,  iColorKeyG,  iColorKeyB));
        }
        p_Source->fSetColorKey(iColorKeyR,iColorKeyG,iColorKeyB);
    }

    /**< Fill map data with init data */
    fInitMap();
}

void cSpriteLayer::fClear()
{
    SDL_Rect rect;
    Uint32 color;
    if(blBuffer)
    {
        color = SDL_MapRGB (sfBuffer->format, 0, 0, 0);
        SDL_FillRect (sfBuffer, NULL, color);
    }
    else
    {
        color = SDL_MapRGB (oWorld->sScreenSurface->format, 0, 0, 0);
        SDL_FillRect (oWorld->sScreenSurface, NULL, color);
    }

}


void cSpriteLayer::fInitLayer(int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, bool blIsBuffered)
{
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

void cSpriteLayer::fSetSpriteHeight(int iPixels)
{
    iSpriteHeight=iPixels;
}

int cSpriteLayer::fGetSpriteHeight()
{
    return iSpriteHeight;
}

void cSpriteLayer::fSetSpriteWidth(int iPixels)
{
    iSpriteWidth=iPixels;
}

int cSpriteLayer::fGetSpriteWidth()
{
    return iSpriteWidth;
}

Uint8 cSpriteLayer::fReturnSpriteFlags(int iRow, int iCol)
{
    return p_LevelData[iRow][iCol].iFlags;
}

void cSpriteLayer::fInitMap()
{
    for (int iRow = 0; iRow < iRowCount; iRow++)
    {
        for (int iCol = 0; iCol < iColCount; iCol++)
        {
            p_LevelData[iRow][iCol].iIndex=1;
            p_LevelData[iRow][iCol].iRow=1;
            p_LevelData[iRow][iCol].iType=EMPTY;
            p_LevelData[iRow][iCol].iFlags=(unsigned char)~(PLATFORM | DAMAGE);
        }
    }
}

cSpriteLayer::~cSpriteLayer()
{
    SDL_FreeSurface(spritelayerscreen);
    SDL_FreeSurface(sfBuffer);
}

SDL_Surface* cSpriteLayer::fRender(signed int CamX, signed int CamY)
{
    // Don't draw things that are outside the view.
    int iStartCol=0;
    int iStartRow=0;
    int iEndCol=iColCount;
    int iEndRow=iRowCount;


    if(blOptmizeLayer)
    {
        iStartCol = fWidthToCol(-CamX);
        iEndCol = fWidthToCol((-CamX)+oWorld->oConfig->m_iScreenWidth);
        iStartRow = fHeightToRow(-CamY);
        iEndRow = fHeightToRow((-CamY)+oWorld->oConfig->m_iScreenHeight);

        // Protect drawing level outside its boundaries
        if(iStartCol<0)
        {
            iStartCol=0;
        }
        if(iStartRow<0)
        {
            iStartRow=0;
        }
        if(iEndCol>iColCount)
        {
            iEndCol=iColCount;
        }
        if(iEndRow>iRowCount)
        {
            iEndRow=iRowCount;
        }
    }

    // Loop
    for (int iRow = iStartRow; iRow < iEndRow; iRow++)
    {
        for (int iCol = iStartCol; iCol < iEndCol; iCol++)
        {
            if(p_LevelData[iRow][iCol].iType!=EMPTY)
                p_Source->fRender(p_LevelData[iRow][iCol].iIndex, p_LevelData[iRow][iCol].iRow, (fColToWidth(iCol)+CamX)+x, (fRowToHeight(iRow)+CamY)+y);
        }
    }

}

SDL_Surface* cSpriteLayer::fGetBufferSurface()
{
    return sfBuffer;
}
int cSpriteLayer::fGetTotalRows()
{
    return iRowCount;
}
int cSpriteLayer::fGetTotalCols()
{
    return iColCount;
}
signed int cSpriteLayer::fColToWidth(signed int iCol)
{
    return (iCol*iSpriteWidth);
}
signed int cSpriteLayer::fRowToHeight(signed int iRow)
{
    return (iRow*iSpriteHeight);
}
signed int cSpriteLayer::fWidthToCol(signed int iWidth)
{
    return (iWidth/iSpriteWidth);
}
signed int cSpriteLayer::fHeightToRow(signed int iHeight)
{
    return (iHeight/iSpriteHeight);
}
signed int cSpriteLayer::fGetWidth()
{
    return iColCount * iSpriteWidth;
}
signed int cSpriteLayer::fGetHeight()
{
    return iRowCount * iSpriteHeight;
}
bool cSpriteLayer::fIsBuffered()
{
    return blBuffer;
}
