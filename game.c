#include <windows.h>
#include <iostream>
#include <fstream>
#include "game.h"

using namespace std;

void cGame::fSave()
{
     
     ofstream myfile;
     myfile.open ("spritelayer.dat",ios::binary);
      
     //Header
     Uint16 iLevelRows=15;
     Uint16 iLevelCols=20;
     Uint16 iSpriteHeight=32;
     Uint16 iSpriteWidth=32;
     Uint8 iSpriteSpacer=2;
     Uint8 iSpriteWidthOffset=0;
     Uint8 iSpriteHeightOffset=0;
     Uint16 iDataBlocks=20;
     
     myfile.write((char*)&iLevelRows,sizeof(Uint16));
     myfile.write((char*)&iLevelCols,sizeof(Uint16));
     myfile.write((char*)&iSpriteHeight,sizeof(Uint16));
     myfile.write((char*)&iSpriteWidth,sizeof(Uint16));
     myfile.write((char*)&iSpriteSpacer,sizeof(Uint8));
     myfile.write((char*)&iSpriteWidthOffset,sizeof(Uint8));
     myfile.write((char*)&iSpriteHeightOffset,sizeof(Uint8));
     myfile.write((char*)&iDataBlocks,sizeof(Uint16));

     // DataBlocks
     for (int iSprite = 0; iSprite < iDataBlocks; iSprite++)
     {
           // Test FIll
           Uint8 iRow=14;
           Uint8 iCol=iSprite;
           Uint8 iType=1;
           Uint8 iSheetRow=1;
           Uint8 iSheetIndex=6;
           // End Test Fill
           
           myfile.write((char*)&iRow,sizeof(Uint8));
           myfile.write((char*)&iCol,sizeof(Uint8));
           myfile.write((char*)&iType,sizeof(Uint8));
           myfile.write((char*)&iSheetRow,sizeof(Uint8));
           myfile.write((char*)&iSheetIndex,sizeof(Uint8));
     
        }
     
     myfile.close();
}


void cGame::Start()
{
     fInitialize();
     fLoadObjects();
     
     while(!blDone)
     {
         fEvents();
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
     
        Uint16 iLevelRows;
        Uint16 iLevelCols;
        Uint16 iSpriteHeight;
        Uint16 iSpriteWidth;
        Uint8 iSpriteSpacer;
        Uint8 iSpriteWidthOffset;
        Uint8 iSpriteHeightOffset;
        Uint16 iDataBlocks;

        std::ifstream oFile;
        oFile.open("spritelayer.dat");

        oFile.read(reinterpret_cast<char*>(&iLevelRows),sizeof(Uint16));
        oFile.read(reinterpret_cast<char*>(&iLevelCols),sizeof(Uint16));
        oFile.read(reinterpret_cast<char*>(&iSpriteHeight),sizeof(Uint16));
        oFile.read(reinterpret_cast<char*>(&iSpriteWidth),sizeof(Uint16));
        oFile.read(reinterpret_cast<char*>(&iSpriteSpacer),sizeof(Uint8));
        oFile.read(reinterpret_cast<char*>(&iSpriteWidthOffset),sizeof(Uint8));
        oFile.read(reinterpret_cast<char*>(&iSpriteHeightOffset),sizeof(Uint8));
        oFile.read(reinterpret_cast<char*>(&iDataBlocks),sizeof(Uint16));

        //Setup Layer
        oLevelLayer = new cSpriteLayer(screen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth); 

        //Setup Source
        oLevelLayer->p_Source->fSetSpriteSpacer(iSpriteSpacer);
        oLevelLayer->p_Source->fLoad("blocks1.bmp");
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
            
            oFile.read(reinterpret_cast<char*>(&iRow),sizeof(Uint8));
            oFile.read(reinterpret_cast<char*>(&iCol),sizeof(Uint8));
            oFile.read(reinterpret_cast<char*>(&iType),sizeof(Uint8));
            oFile.read(reinterpret_cast<char*>(&iSheetRow),sizeof(Uint8));
            oFile.read(reinterpret_cast<char*>(&iSheetIndex),sizeof(Uint8));
        
            oLevelLayer->p_LevelData[iRow][iCol].iType=iType;
            oLevelLayer->p_LevelData[iRow][iCol].iRow=iSheetRow;
            oLevelLayer->p_LevelData[iRow][iCol].iIndex=iSheetIndex;                    
         }

        //End Level Layer
  
  
  
  
  
    
    //Player Layer 
        iLevelRows=1;
        iLevelCols=1;
        iSpriteHeight=32;
        iSpriteWidth=32;
        // 15 (rows) x 20 (cols) of 32px sprites (640x480)
         
        //Setup Layer
        oPlayerLayer = new cSpriteLayer(screen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth); 
        
        //Setup Source
        oPlayerLayer->p_Source->fSetSpriteSpacer(2);
        oPlayerLayer->p_Source->fLoad("blocks1.bmp");
        oPlayerLayer->p_Source->fSetSpriteWidthOffset(0);
        oPlayerLayer->p_Source->fSetSpriteHeightOffset(0);
        oPlayerLayer->p_Source->fSetSpriteHeight(iSpriteHeight);
        oPlayerLayer->p_Source->fSetSpriteWidth(iSpriteWidth);
        
        //Setup Player
        oPlayerLayer->p_LevelData[0][0].iType=SPRITE;
        oPlayerLayer->p_LevelData[0][0].iRow=10;
        oPlayerLayer->p_LevelData[0][0].iIndex=0;

    //End Level Layer
    
     
}

     
void cGame::fGameLoop()
{
        if(oPlayerLayer->p_LevelData[0][0].iIndex == 10)
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
    
    SDL_WM_SetCaption ("Dungeon test", NULL);

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
                    CamX += 1;
                    break;
                    
                    case SDLK_RIGHT:
                    CamX -= 1;
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
}

cGame::~cGame()
{}

void cGame::fCleanUp()
{
    //Destroy objects
    delete oLevelLayer;
    SDL_FreeSurface(screen);
}
                
/* This function draws to the screen; replace this with your own code! */
void cGame::fRender()
{
    SDL_Rect rect;
    Uint32 color;

    /* Create a black background */
    color = SDL_MapRGB (screen->format, 0, 0, 0);
    
    SDL_FillRect (screen, NULL, color);

    if(blSpritePalet){
    oBackgroundLayer->fRender(0,0,CamX,CamY);
    }
    oLevelLayer->fRender(CamX,CamY);
    oPlayerLayer->fRender(CamX,CamY);
    
    
    /* Make sure everything is displayed on screen */
    SDL_Flip (screen);    
}
