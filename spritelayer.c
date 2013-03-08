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

cSpriteLayer::cSpriteLayer(SDL_Surface *screen, int iRows, int iCols, int iSpriteHeightPX, int iSpriteWidthPX)
{ 
                                       
   iSpriteHeight=iSpriteHeightPX;
   iSpriteWidth=iSpriteWidthPX;
   
   iRowCount=iRows;
   iColCount=iCols;
                                       
   //create data object
   p_LevelData = new sLevelBlock*[iRows];
   for(int i=0; i < iRows; i++)
      p_LevelData[i] = new sLevelBlock[iCols];
   
   //screen
   spritelayerscreen = screen;    
   
   //setup source object
   p_Source = new cSprite(spritelayerscreen);                               
       
   fInitMap();                                                        
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

SDL_Surface* cSpriteLayer::fRender(int CamX, int CamY)
{  
                      
   for (int iRow = 0; iRow < iRowCount; iRow++)
   {
       for (int iCol = 0; iCol < iColCount; iCol++)
       {
           if(p_LevelData[iRow][iCol].iType!=EMPTY)
           p_Source->fRender(p_LevelData[iRow][iCol].iIndex, p_LevelData[iRow][iCol].iRow, (fColToWidth(iCol)+CamX), (fRowToHeight(iRow)+CamY));
       }    
   }               
}


int cSpriteLayer::fColToWidth(int iCol)

{
    return (iCol*iSpriteWidth);
}

int cSpriteLayer::fRowToHeight(int iRow)
{
    return (iRow*iSpriteHeight);
}
