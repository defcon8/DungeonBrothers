/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with DevC++ on Win32.
  2013
  
  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <windows.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include "game.h"

using namespace std;

void cGame::fSave()
{
     
     ofstream oSave;
     oSave.open ("spritelayer.dat",ios::binary);
      
     //Header
     char chTileSource[16]="blocks1.bmp";
     Uint16 iLevelRows=15; //15 is 1 full screen at 640x480
     Uint16 iLevelCols=40; //20 is 1 full screen at 640x480
     Uint16 iSpriteHeight=32;
     Uint16 iSpriteWidth=32;
     Uint16 iSourceRows=11;
     Uint16 iSourceCols=18;
     Uint8 iSpriteSpacer=2;
     Uint8 iSpriteWidthOffset=0;
     Uint8 iSpriteHeightOffset=0;
     Uint16 iDataBlocks=40;
     
     oSave.write((char*)&chTileSource,sizeof(chTileSource));
     oSave.write((char*)&iLevelRows,sizeof(Uint16));
     oSave.write((char*)&iLevelCols,sizeof(Uint16));
     oSave.write((char*)&iSpriteHeight,sizeof(Uint16));
     oSave.write((char*)&iSpriteWidth,sizeof(Uint16));
     oSave.write((char*)&iSourceRows,sizeof(Uint16));
     oSave.write((char*)&iSourceCols,sizeof(Uint16));
     oSave.write((char*)&iSpriteSpacer,sizeof(Uint8));
     oSave.write((char*)&iSpriteWidthOffset,sizeof(Uint8));
     oSave.write((char*)&iSpriteHeightOffset,sizeof(Uint8));
     oSave.write((char*)&iDataBlocks,sizeof(Uint16));

     // DataBlocks
     for (int iSprite = 0; iSprite < iDataBlocks; iSprite++)
     {
           // Test Fill
           Uint8 iRow=14;
           Uint8 iCol=iSprite;
           Uint8 iType=1;
           Uint8 iSheetRow=1;
           Uint8 iSheetIndex=6;
           // End Test Fill
           
           oSave.write((char*)&iRow,sizeof(Uint8));
           oSave.write((char*)&iCol,sizeof(Uint8));
           oSave.write((char*)&iType,sizeof(Uint8));
           oSave.write((char*)&iSheetRow,sizeof(Uint8));
           oSave.write((char*)&iSheetIndex,sizeof(Uint8));
      }
     
      oSave.close();
}


void cGame::Start()
{
     fInitialize();
     fLoadObjects();
     
     while(!blDone)
     {          
         fEvents();
         fCameraMovement();
         fGameLoop();
         fRender();
         
         /* Don't run too fast */
         SDL_Delay (1); //50Hz           
     }
     
     fCleanUp();    
}

void cGame::fLoadObjects()
{
      //Background Layer
        oBackgroundLayer = new cSprite(screen);
        oBackgroundLayer->fLoad("back.bmp");
        oBackgroundLayer->fSetSpriteWidth(640);
        oBackgroundLayer->fSetSpriteHeight(480);
        oBackgroundLayer->fScroll(0);

        //Level Layer
     
        char chTileSource[16];
        Uint16 iLevelRows;
        Uint16 iLevelCols;
        Uint16 iSpriteHeight;
        Uint16 iSpriteWidth;
        Uint16 iSourceRows;
        Uint16 iSourceCols;
        Uint8 iSpriteSpacer;
        Uint8 iSpriteWidthOffset;
        Uint8 iSpriteHeightOffset;
        Uint16 iDataBlocks;

        std::ifstream oLoad;
        oLoad.open("spritelayer.dat");

        oLoad.read(reinterpret_cast<char*>(&chTileSource),sizeof(chTileSource));
        oLoad.read(reinterpret_cast<char*>(&iLevelRows),sizeof(Uint16));
        oLoad.read(reinterpret_cast<char*>(&iLevelCols),sizeof(Uint16));
        oLoad.read(reinterpret_cast<char*>(&iSpriteHeight),sizeof(Uint16));
        oLoad.read(reinterpret_cast<char*>(&iSpriteWidth),sizeof(Uint16));
        oLoad.read(reinterpret_cast<char*>(&iSourceRows),sizeof(Uint16));
        oLoad.read(reinterpret_cast<char*>(&iSourceCols),sizeof(Uint16));
        oLoad.read(reinterpret_cast<char*>(&iSpriteSpacer),sizeof(Uint8));
        oLoad.read(reinterpret_cast<char*>(&iSpriteWidthOffset),sizeof(Uint8));
        oLoad.read(reinterpret_cast<char*>(&iSpriteHeightOffset),sizeof(Uint8));
        oLoad.read(reinterpret_cast<char*>(&iDataBlocks),sizeof(Uint16));

        //Setup Layer
        oLevelLayer = new cSpriteLayer(screen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth); 

        //Setup Source
        oLevelLayer->p_Source->fSetSpriteSpacer(iSpriteSpacer);
        oLevelLayer->p_Source->fLoad(chTileSource);
        oLevelLayer->p_Source->fSetSpriteWidthOffset(iSpriteWidthOffset);
        oLevelLayer->p_Source->fSetSpriteHeightOffset(iSpriteHeightOffset);
        oLevelLayer->p_Source->fSetSpriteHeight(iSpriteHeight);
        oLevelLayer->p_Source->fSetSpriteWidth(iSpriteWidth);
        
         // DataBlocks
         for (int iSprite = 0; iSprite < iDataBlocks; iSprite++)
         {
            Uint8 iRow;
            Uint8 iCol;
            Uint8 iType;
            Uint8 iSheetRow;
            Uint8 iSheetIndex;
            
            oLoad.read(reinterpret_cast<char*>(&iRow),sizeof(Uint8));
            oLoad.read(reinterpret_cast<char*>(&iCol),sizeof(Uint8));
            oLoad.read(reinterpret_cast<char*>(&iType),sizeof(Uint8));
            oLoad.read(reinterpret_cast<char*>(&iSheetRow),sizeof(Uint8));
            oLoad.read(reinterpret_cast<char*>(&iSheetIndex),sizeof(Uint8));
        
            oLevelLayer->p_LevelData[iRow][iCol].iType=iType;
            oLevelLayer->p_LevelData[iRow][iCol].iRow=iSheetRow;
            oLevelLayer->p_LevelData[iRow][iCol].iIndex=iSheetIndex;                    
         }
        //End Level Layer
  
        //Start Player Layer 
        iLevelRows=1;
        iLevelCols=1;
        iSpriteHeight=32;
        iSpriteWidth=32;
        // 15 (rows) x 20 (cols) of 32px sprites (640x480)
         
        //Setup Layer
        oPlayerLayer = new cSpriteLayer(screen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth); 
        
        //Setup Source
        oPlayerLayer->p_Source->fSetSpriteSpacer(2);
        oPlayerLayer->p_Source->fLoad(chTileSource);
        oPlayerLayer->p_Source->fSetSpriteWidthOffset(0);
        oPlayerLayer->p_Source->fSetSpriteHeightOffset(0);
        oPlayerLayer->p_Source->fSetSpriteHeight(iSpriteHeight);
        oPlayerLayer->p_Source->fSetSpriteWidth(iSpriteWidth);
        
        //Setup Player
        oPlayerLayer->p_LevelData[0][0].iType=SPRITE;
        oPlayerLayer->p_LevelData[0][0].iRow=10;
        oPlayerLayer->p_LevelData[0][0].iIndex=0;

        //End Player Layer

        oLoad.close();
        
        //Start sprite picker layer (for edit mode only)
        oSpritePicker = new cSpriteLayer(screen,iSourceRows,iSourceCols,iSpriteHeight,iSpriteWidth);
        oSpritePicker->p_Source->fSetSpriteSpacer(2);
        oSpritePicker->p_Source->fLoad(chTileSource);
        oSpritePicker->p_Source->fSetSpriteWidthOffset(0);
        oSpritePicker->p_Source->fSetSpriteHeightOffset(0);
        oSpritePicker->p_Source->fSetSpriteHeight(iSpriteHeight);
        oSpritePicker->p_Source->fSetSpriteWidth(iSpriteWidth);
        
         for (int iCol = 0; iCol < iSourceCols; iCol++)
         {
             for (int iRow = 0; iRow < iSourceRows; iRow++)
             {
                 oSpritePicker->p_LevelData[iRow][iCol].iType=SPRITE;
                 oSpritePicker->p_LevelData[iRow][iCol].iRow=iRow;
                 oSpritePicker->p_LevelData[iRow][iCol].iIndex=iCol;
             }
         }  
}

void cGame::fGameLoop()
{
        if(oPlayerLayer->p_LevelData[0][0].iIndex==10)
        {
              oPlayerLayer->p_LevelData[0][0].iIndex=0;
        }else{
              oPlayerLayer->p_LevelData[0][0].iIndex+=1;
        }                
}
     
void cGame::fInitialize()
{
    char *chMessage;

    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        sprintf (chMessage, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        MessageBox (0, chMessage, "Error", MB_ICONHAND); 
        free(chMessage);
        exit(1);
    }
    atexit (SDL_Quit);

    /* Set 640x480 16-bits video mode */
    screen = SDL_SetVideoMode (640, 480, 16, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        sprintf (chMessage, "Couldn't set 640x480x16 video mode: %s\n",
        SDL_GetError ());
        MessageBox (0, chMessage, "Error", MB_ICONHAND); 
        free(chMessage);
        exit(2);
    }
    
    SDL_WM_SetCaption ("Dungeon Brothers", NULL);
    //SDL_ShowCursor(SDL_DISABLE); 
}

void cGame::fEvents()
{
     if(blEditMode)
     {
       fEditModeEvents();
     }else{
       fNormalModeEvents();
     }                  
}      

void cGame::fNormalModeEvents()
{
    SDL_Event event;
        /* Check for events */
        while (SDL_PollEvent (&event))
        {
           switch (event.type)
            {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {                 
                    case SDLK_ESCAPE:
                         blEditMode = true;
                    break;                                   
                } 
                break;
            case SDL_QUIT:
                blDone = 1;
                break;
            default:
                break;
            }
        }     
}

void cGame::fEditModeEvents()
{         
        SDL_Event event;
        /* Check for events */
        while (SDL_PollEvent (&event))
        {
           switch (event.type)
            {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {                 
                    case SDLK_ESCAPE:
                         blEditMode = false;
                    break;      
                    
                    case SDLK_F1:
                         blSpritePalet = !blSpritePalet;
                         break;                    
                                            
                    case SDLK_LEFT:
                    iCamDirection=LEFT;
                    break;
                    
                    case SDLK_RIGHT:
                    iCamDirection=RIGHT;
                    break;
                    
                    case SDLK_UP:
                    iCamDirection=UP;
                    break;
                    
                    case SDLK_DOWN:
                    iCamDirection=DOWN;
                    break;
                } 
                break;
            
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {                                               
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                    case SDLK_UP:
                    case SDLK_DOWN:
                         iCamDirection=NONE;
                    break;
                }
                break;
                 
            case SDL_QUIT:
                blDone = 1;
                break;
            default:
                break;
            }
        } 
        
        //Camera movement by mouse
        int x,y;
        SDL_GetMouseState(&x, &y); 
        if(x>635)
                 CamX--;
        if(x<5)
                 CamX++;
        if(y>475)
                 CamY--;
        if(y<5)
                 CamY++;     
}

void cGame::fCameraMovement()
{
  //Do Camera movement
        switch(iCamDirection)
        {
            case 1:
                 CamY += 1;
                 break;
            case 2:
                 CamX -= 1;
                 break;
            case 3:
                 CamY -= 1;
                 break;
            case 4:
                 CamX += 1;
                 break;                     
        }
}

cGame::cGame()
{
      //constructor
      fSave();
      fInitVariables();
}

void cGame::fInitVariables()
{
      blDone = false;
      blEditMode = false;
      blSpritePalet = false;
      CamX=0;
      CamY=0;
      iCamDirection=0;
      MouseX=0;
      MouseY=0;                     
}

cGame::~cGame()
{}

void cGame::fCleanUp()
{
    //Destroy objects
    delete oLevelLayer;
    SDL_FreeSurface(screen);
}
        
void cGame::fRenderEditMode()
{
        // Get position of mouse  
        int x, y;
        int iMouseButtons = SDL_GetMouseState(&x, &y); 
        
        int iTileWidth = oLevelLayer->fGetSpriteWidth();
        int iTileHeight = oLevelLayer->fGetSpriteHeight();

        int iTileCol = fGetTileCol(x,iTileWidth);
        int iTileRow = fGetTileRow(y,iTileHeight);
        
        int iRectX = (iTileCol*iTileWidth);
        int iRectY = (iTileRow*iTileHeight);
        
        //Draw tile placeholder
        fDrawRectangle(iRectX,iRectY,iTileWidth,iTileHeight,0xFFFFFF);
        
        //Recalculate the real tile using the camera offset
        iTileCol = fGetTileCol(x-CamX,iTileWidth);
        iTileRow = fGetTileRow(y-CamY,iTileHeight);  
        
        switch(iMouseButtons)
        {
           case 1:                  
           //Left button, Draw
           oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=2;
           oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=SPRITE;
           break;
           
           case 4:
           //Right button, Clear
           oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=0;
           oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=EMPTY;
           break;
        } 
}        

int cGame::fGetTileCol(int iX, int iTileWidth){return static_cast<int>(floor(iX/iTileWidth));}
int cGame::fGetTileRow(int iY, int iTileHeight){return static_cast<int>(floor(iY/iTileHeight));}

void cGame::fDrawRectangle(int x, int y, int w, int h, Uint32 color)
{
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;       
        SDL_FillRect(screen,&rect,color);
}
                
void cGame::fRender()
{
    SDL_Rect rect;
    Uint32 color;

    /* Create a black background */
    color = SDL_MapRGB (screen->format, 0, 0, 0);
    
    SDL_FillRect (screen, NULL, color);

    //if(blSpritePalet){
    //   oBackgroundLayer->fRender(0,0,CamX,CamY);
    //}
 
    oLevelLayer->fRender(CamX,CamY);
    oPlayerLayer->fRender(CamX,CamY);
    
    if(blEditMode)
    {
       if(blSpritePalet)
       {
          oSpritePicker->fRender(CamX,CamY);                 
       }   
       fRenderEditMode();
    }
    
    /* Make sure everything is displayed on screen */
    SDL_Flip (screen);    
}

void cGame::fDrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B) 
{ 
  Uint32 color = SDL_MapRGB(screen->format, R, G, B); 
  switch (screen->format->BytesPerPixel) 
  { 
    case 1: // 8-bpp 
      { 
        Uint8 *bufp; 
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x; 
        *bufp = color; 
      } 
      break; 
    case 2: // 15-bpp or 16-bpp 
      { 
        Uint16 *bufp; 
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x; 
        *bufp = color; 
      } 
      break; 
    case 3: // 24-bpp mode, usually not used 
      { 
        Uint8 *bufp; 
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3; 
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN) 
        { 
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
    case 4: // 32-bpp 
      { 
        Uint32 *bufp; 
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x; 
        *bufp = color; 
      } 
      break; 
  } 
} 
