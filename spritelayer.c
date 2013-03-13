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
//SDL_Surface *masterscreen;

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
   //masterscreen = screen;
   spritelayerscreen = screen;
   //spritelayerscreen = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h,screen->format->BitsPerPixel,screen->format->Rmask,screen->format->Gmask,screen->format->Bmask,screen->format->Amask));
   
   //if(!spritelayerscreen)
   //{
		// std::cerr << "CreateEmptySurface() - Something went wrong creating a " << width << "x" << height << " surface.\n"
				 // << "	Error: " << SDL_GetError() << std::endl;
				 //bla
   //}
      
   //setup source object
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
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    r = 0xff000000;
    g = 0x00ff0000;
    b = 0x0000ff00;
    a = 0x000000ff;
#else
    r = 0x000000ff;
    g = 0x0000ff00;
    b = 0x00ff0000;
    a = 0xff000000;
#endif

    // Here's the actual magic.
    //Create a new surface via SDL_CreateRGBSurface() by providing:
    //    The flags you want (I only tested with SDL_SWSURFACE).
    //    The dimension of the new surface.
    //    The bitrate you want to use.
    //    The mask values you just created.
    //Then convert it to match the display's format. (this was the crucial part that fixed it for me)
    SDL_Surface* subSurface = SDL_DisplayFormat(SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, r, g, b, a));

    // Lastly, apply the area from the meta surface onto the whole of the sub surface.
    SDL_BlitSurface(metaSurface, &area, subSurface, 0);

    // Return the newly created surface!
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

   //SDL_BlitSurface(spritelayerscreen, NULL, masterscreen, NULL);     
}


int cSpriteLayer::fColToWidth(int iCol)

{
    return (iCol*iSpriteWidth);
}

int cSpriteLayer::fRowToHeight(int iRow)
{
    return (iRow*iSpriteHeight);
}
