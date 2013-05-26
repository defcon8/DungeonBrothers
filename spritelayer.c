/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with DevC++ on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include "spritelayer.h"
#include <cstring>
#include <fstream>

using namespace std;

SDL_Surface *spritelayerscreen;

cSpriteLayer::cSpriteLayer(SDL_Surface *screen, int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX, bool blOptimize, int iScreenWidthRef, int iScreenHeightRef)
{
   iSpriteHeight=iSpriteHeightPX;
   iSpriteWidth=iSpriteWidthPX;

   iScreenWidth = iScreenWidthRef;
   iScreenHeight = iScreenHeightRef;

   //initialise
   x=0;
   y=0;

   iRowCount=iRows;
   iColCount=iCols;

   blOptmizeLayer=blOptimize;

   //create data object
   p_LevelData = new sLevelBlock*[iRows];
   for(int i=0; i < iRows; i++)
      p_LevelData[i] = new sLevelBlock[iCols];

   //screen
   spritelayerscreen = screen;

   //Setup (source) object that contains the Sprite Sheet.
   p_Source = new cSprite(spritelayerscreen);

   fInitMap();
}

SDL_Surface* cSpriteLayer::Get_Sub_Surface(SDL_Surface* metaSurface, int x, int y, int width, int height)
{
    // Create an SDL_Rect with the area of the surface you want to create.
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = width;
    area.h = height;

    // Set the RGBA mask values.
    Uint32 r, g, b, a;
   if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
   {
        r = 0xff000000;
        g = 0x00ff0000;
        b = 0x0000ff00;
        a = 0x000000ff;
    }else{
        r = 0x000000ff;
        g = 0x0000ff00;
        b = 0x00ff0000;
        a = 0xff000000;
    }

    SDL_Surface* subSurface = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, r, g, b, a));

    // Lastly, apply the area from the meta surface onto the whole of the sub surface.
    SDL_BlitSurface(metaSurface, &area, subSurface, 0);

    // Return the newly created surface.
    return subSurface;
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
            p_LevelData[iRow][iCol].iFlags=PLATFORM | DAMAGE;
       }
   }
}

int cSpriteLayer::fGetTotalRows() { return iRowCount; }

int cSpriteLayer::fGetTotalCols() { return iColCount; }

cSpriteLayer::~cSpriteLayer()
{
   SDL_FreeSurface(spritelayerscreen);
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
        iEndCol = fWidthToCol((-CamX)+iScreenWidth);
        iStartRow = fHeightToRow(-CamY);
        iEndRow = fHeightToRow((-CamY)+iScreenHeight);

        // Protect drawing level outside its boundaries
        if(iStartCol<0){ iStartCol=0; }
        if(iStartRow<0){ iStartRow=0; }
        if(iEndCol>iColCount){ iEndCol=iColCount; }
        if(iEndRow>iRowCount){ iEndRow=iRowCount; }
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

