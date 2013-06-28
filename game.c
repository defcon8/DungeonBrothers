// *** ADDED BY HEADER FIXUP ***
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <list>
// *** END ***
/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <windows.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <cstring>
#include "game.h"

using namespace std;

void cGame::fSaveLayer(cSpriteLayer *p_SpriteLayer)
{
    ofstream oSave;
    oSave.open ("spritelayer.dat",ios::binary);

    //Header
    char chTileSource[16];
    memcpy(&chTileSource[0],p_SpriteLayer->p_Source->fGetTileSource(),16);

    Uint16 iLevelRows = p_SpriteLayer->fGetTotalRows();
    Uint16 iLevelCols = p_SpriteLayer->fGetTotalCols();
    Uint16 iSpriteHeight = p_SpriteLayer->fGetSpriteHeight();
    Uint16 iSpriteWidth = p_SpriteLayer->fGetSpriteWidth();;
    Uint16 iSourceRows=11;
    Uint16 iSourceCols=18;
    Uint8 iSpriteSpacer=2;
    Uint8 iSpriteWidthOffset=0;
    Uint8 iSpriteHeightOffset=0;
    Uint16 iDataBlocks=(iLevelRows*iLevelCols); // Count the nr of blocks

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
    for (int iRow = 0; iRow <= (iLevelRows-1)  ; iRow++ )
    {
        for (int iCol = 0; iCol <= (iLevelCols-1) ; iCol++ )
        {
            Uint8 iType=p_SpriteLayer->p_LevelData[iRow][iCol].iType;
            Uint8 iSheetRow=p_SpriteLayer->p_LevelData[iRow][iCol].iRow;
            Uint8 iSheetIndex=p_SpriteLayer->p_LevelData[iRow][iCol].iIndex;

            oSave.write((char*)&iRow,sizeof(Uint8));
            oSave.write((char*)&iCol,sizeof(Uint8));
            oSave.write((char*)&iType,sizeof(Uint8));
            oSave.write((char*)&iSheetRow,sizeof(Uint8));
            oSave.write((char*)&iSheetIndex,sizeof(Uint8));
        }
    }
    oSave.close();
}

void cGame::fSaveDemo()
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

void cGame::fCameraMovement()
{
    if(!blEditMode) // Dont move camera automaticly when in edit mode because we want to move by mouse
    {
        int iPos;
        //Let the camera follow the players position. If the camera position is not optimal then increase or decrease the camera position by 1 to have a smooth scrolling effect. Do not follow
        //when the user is jumping..this is kind a hectic.

        //Left/Right
        iPos = -(oWorld->oPlayerObject->X - (oWorld->oConfig->m_iScreenWidth/2) - oWorld->oPlayerObject->oGFXLayer->fGetWidth());

        if(iPos < oWorld->oCam->X)
        {
            // Let the Camera go left
            oWorld->oCam->X-=oWorld->oCam->iVelocityCam;
        }
        else if(iPos > oWorld->oCam->X)
        {
            // Let the Camera go left
            oWorld->oCam->X+=oWorld->oCam->iVelocityCam;
        }

        //Up/Down
        if(!oWorld->oPlayerObject->blIsJumping) //Do not update camera on player jump
        {
            iPos = -(oWorld->oPlayerObject->Y - (oWorld->oConfig->m_iScreenHeight/2) - oWorld->oPlayerObject->oGFXLayer->fGetHeight());
            if(iPos < oWorld->oCam->Y)
            {
                // Let the Camera go up
                oWorld->oCam->Y--;
            }
            else if(iPos > oWorld->oCam->Y)
            {
                // Let the Camera go down
                oWorld->oCam->Y++;
            }
            else
            {
                // The camera is in optimal position
            }
        }
    }
}

void cGame::Start()
{
    fInitialize();
    fLoadObjects();

    while(!blDone)
    {
        long measure1 = time(NULL);
        fEvents();
        fObjectMovement();
        fCameraMovement();
        fGameLoop();
        fRender();
        iRenderedFrames++;
        fFPS();
        long measure2 = time(NULL); //Give system time to the OS, prevent 100% Core usage.
        long diff = measure2 - measure1;
        SDL_Delay(13-diff); // sleep until next tick
    }
    fCleanUp();
}

void cGame::fFPS()
{
    iElapsedSeconds=time(NULL)-iStartTime;
    if(iElapsedSeconds>0) //Protect against divide by zero, crash at program startup.
        iFPS=iRenderedFrames/iElapsedSeconds;
}

void cGame::fLoadObjects()
{
    //Background Layer
    oWorld->oBackgroundLayer = new cSprite(oWorld);
    oWorld->oBackgroundLayer->fLoad("back.bmp");
    oWorld->oBackgroundLayer->iSpriteWidth = 6400;
    oWorld->oBackgroundLayer->iSpriteHeight = 480;

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
    oLoad.open("spritelayer.dat", ios_base::in | ios_base::binary);

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

    // ------------ [ start setup level ] --------------------
    oWorld->oLevelLayer = new cSpriteLayer(oWorld,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth,false,true,true,0,0,0);

    //Setup Source
    oWorld->oLevelLayer->p_Source->iSpriteSpacer = iSpriteSpacer;
    oWorld->oLevelLayer->p_Source->fLoad(chTileSource);
    oWorld->oLevelLayer->p_Source->iSpriteWidthOffset = iSpriteWidthOffset;
    oWorld->oLevelLayer->p_Source->iSpriteHeightOffset = iSpriteHeightOffset;
    oWorld->oLevelLayer->p_Source->iSpriteHeight = iSpriteHeight;
    oWorld->oLevelLayer->p_Source->iSpriteWidth = iSpriteWidth;

    // Read DataBlocks from file
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

        oWorld->oLevelLayer->p_LevelData[iRow][iCol].iType=iType;
        oWorld->oLevelLayer->p_LevelData[iRow][iCol].iRow=iSheetRow;
        oWorld->oLevelLayer->p_LevelData[iRow][iCol].iIndex=iSheetIndex;
    }

    oWorld->oLevelLayer->fRender(0,0); //Because this is a buffered layer, we render it once direct after construction of the data array.

    // ------------ [ start setup player ] --------------------

    char chPlayerBitmap[]="player.bmp";
    oWorld->oPlayerObject = new cPlayer(oWorld, chPlayerBitmap,40,32);
    oWorld->lLevelObjects.push_back(oWorld->oPlayerObject);    //Add to level object list

    //Close File
    oLoad.close();

    // ------------ [ start setup spritepicker ] --------------------
    oWorld->oSpritePicker = new cSpriteLayer(oWorld,iSourceRows,iSourceCols,iSpriteHeight,iSpriteWidth,false,false,false,0,0,0);
    oWorld->oSpritePicker->p_Source->iSpriteSpacer = 2;
    oWorld->oSpritePicker->p_Source->fLoad(chTileSource);
    oWorld->oSpritePicker->p_Source->iSpriteWidthOffset = 0;
    oWorld->oSpritePicker->p_Source->iSpriteHeightOffset = 0;
    oWorld->oSpritePicker->p_Source->iSpriteHeight = iSpriteHeight;
    oWorld->oSpritePicker->p_Source->iSpriteWidth = iSpriteWidth;

    for (int iCol = 0; iCol < iSourceCols; iCol++)
    {
        for (int iRow = 0; iRow < iSourceRows; iRow++)
        {
            oWorld->oSpritePicker->p_LevelData[iRow][iCol].iType=SPRITE;
            oWorld->oSpritePicker->p_LevelData[iRow][iCol].iRow=iRow;
            oWorld->oSpritePicker->p_LevelData[iRow][iCol].iIndex=iCol;
        }
    }
}

void cGame::fGameLoop()
{
//    /**<  Test: Player Collision detection - Level Boundaries */
//    if(oPlayerLayer->x < 0 || oPlayerLayer->x > oLevelLayer->fGetWidth() || oPlayerLayer->y < 0 || oPlayerLayer->y > oLevelLayer->fGetHeight())
//    {
//        oPlayerLayer->p_LevelData[0][0].iIndex=10;
//    }else{
//        oPlayerLayer->p_LevelData[0][0].iIndex=3;
//    }
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

    TTF_Init();
    ttfFont = TTF_OpenFont("Fonts\\BeckerBlackNF.ttf", 20);

    if (ttfFont == NULL)
    {
        sprintf (chMessage, "Can't load font.");
        SDL_GetError ();
        MessageBox(0,chMessage,"Error",MB_ICONHAND);
        free(chMessage);
        exit(2);
    }

    atexit (SDL_Quit);
    oWorld->sScreenSurface = SDL_SetVideoMode (oWorld->oConfig->m_iScreenWidth, oWorld->oConfig->m_iScreenHeight, oWorld->oConfig->m_iScreenBits, oWorld->oConfig->iSDLFlags);
    if (oWorld->sScreenSurface == NULL)
    {
        sprintf (chMessage, "Couldn't set video mode: %s\n", SDL_GetError ());
        MessageBox (0, chMessage, "Error", MB_ICONHAND);
        free(chMessage);
        exit(2);
    }

    SDL_WM_SetCaption ("Dungeon Brothers", NULL);
    SDL_ShowCursor(SDL_DISABLE);
}

void cGame::fEvents()
{
    if(blEditMode)
    {
        fEditModeEvents();
    }
    else
    {
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
            case SDLK_UP:
                oWorld->oPlayerObject->fMoveDirection(1,true);
                break;
            case SDLK_RIGHT:
                oWorld->oPlayerObject->fMoveDirection(2,true);
                break;
            case SDLK_DOWN :
                oWorld->oPlayerObject->fMoveDirection(3,true);
                break;
            case SDLK_LEFT:
                oWorld->oPlayerObject->fMoveDirection(4,true);
                break;
            case SDLK_ESCAPE:
                blDone=true;
                blEditMode = true;
                break;
            case SDLK_F1:
                //Toggle Edit Mode
                blEditMode = !blEditMode;
                SDL_WM_SetCaption ("Edit mode", NULL);
                break;
            case SDLK_SPACE:
                if(!oWorld->oPlayerObject->blIsJumping)
                    oWorld->oPlayerObject->fJump();
                break;
            case SDLK_LALT:
                oWorld->oPlayerObject->fFire();
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
            {
                oWorld->oPlayerObject->fMoveDirection(1,false);
                break;
            }

            case SDLK_RIGHT:
            {
                oWorld->oPlayerObject->fMoveDirection(2,false);
                break;
            }
            case SDLK_DOWN:
            {
                oWorld->oPlayerObject->fMoveDirection(3,false);
                break;
            }
            case SDLK_LEFT:
            {
                oWorld->oPlayerObject->fMoveDirection(4,false);
                break;
            }
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
                // Exit program
                blDone = true;
                break;

            case SDLK_F1:
                //Toggle Edit mode
                blEditMode = !blEditMode; // Exit edit mode
                blSpritePalet = false;    // Hide SpritePicker
                blRenderLevel = true;     // Show Level
                SDL_WM_SetCaption ("Normal mode", NULL);
                break;

            case SDLK_F2:
                //Toggle Sprite Picker
                if(blSpritePalet)
                {
                    blSpritePalet = false;  // Hide Sprite Picker
                    blRenderLevel = true;   // Hide Level
                    SDL_WM_SetCaption ("Edit mode - Level editor", NULL);
                }
                else
                {
                    blSpritePalet = true;  // Hide Sprite Picker
                    blRenderLevel = false;   // Hide Level
                    SDL_WM_SetCaption ("Edit mode - Level editor", NULL);
                }
                break;

            case SDLK_F3:
                //Save Layer to File
                fSaveLayer(oWorld->oLevelLayer);
                SDL_WM_SetCaption ("Current Layer Saved.", NULL);
                break;

            case SDLK_F4:
                //Save Demo
                fSaveDemo();
                SDL_WM_SetCaption ("Basic demolevel Saved.", NULL);
                break;

            case SDLK_LEFT:
                oWorld->oCam->Direction=oWorld->oCam->left;
                break;

            case SDLK_RIGHT:
                oWorld->oCam->Direction=oWorld->oCam->right;
                break;

            case SDLK_UP:
                oWorld->oCam->Direction=oWorld->oCam->up;
                break;

            case SDLK_DOWN:
                oWorld->oCam->Direction=oWorld->oCam->down;
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
                oWorld->oCam->Direction=oWorld->oCam->none;
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

    //Camera movement by mouse corners to navigate thru the scene
    int x,y;
    SDL_GetMouseState(&x, &y);
    if(x>(oWorld->oConfig->m_iScreenWidth*dbMouseCornerWidthPerc))
        oWorld->oCam->X-=iMouseScrollSpeed;
    if(x<(oWorld->oConfig->m_iScreenWidth*(1.0 - dbMouseCornerWidthPerc))) // Invert
        oWorld->oCam->X+=iMouseScrollSpeed;
    if(y>(oWorld->oConfig->m_iScreenHeight*dbMouseCornerWidthPerc))
        oWorld->oCam->Y-=iMouseScrollSpeed;
    if(y<(oWorld->oConfig->m_iScreenHeight*(1.0 - dbMouseCornerWidthPerc)))
        oWorld->oCam->Y+=iMouseScrollSpeed;
}

void cGame::fObjectMovement()
{
    //Do Camera movement
    switch(oWorld->oCam->Direction)
    {
    case 1:
        oWorld->oCam->Y += 1;
        break;
    case 2:
        oWorld->oCam->X -= 1;
        break;
    case 3:
        oWorld->oCam->Y -= 1;
        break;
    case 4:
        oWorld->oCam->X += 1;
        break;
    }
}

cGame::cGame()
{
    oWorld = new cWorld();
    fInitVariables();
}

void cGame::fInitVariables()
{
    blDone = false;
    blEditMode = false;
    blRenderLevel = true;
    blSpritePalet = false;
    MouseX=0;
    MouseY=0;
    dbMouseCornerWidthPerc=0.95;
    iMouseScrollSpeed=5;
    iElapsedSeconds=0;
    iOptimalFrequency=30; // 30 FPS
    iStartTime=time(NULL);
    iRenderedFrames=0;
    iFPS=0;

    //GUI Related
    cBlack.r=0;
    cBlack.g=0;
    cBlack.b=0;
    cGreen.r=0;
    cGreen.g=255;
    cGreen.b=0;
    rFPSLocation.x=30;
    rFPSLocation.y=oWorld->oConfig->m_iScreenHeight-50;
}

cGame::~cGame()
{}

void cGame::fCleanUp()
{
    //Destroy objects
    delete oWorld->oLevelLayer;
    SDL_FreeSurface(oWorld->sTextSurface);
    SDL_FreeSurface(oWorld->sScreenSurface);
}

void cGame::fRenderEditMode()
{
    // Get position of mouse and calculate the according position in tiles/rows
    int iMouseX, iMouseY;
    int iMouseButtons = SDL_GetMouseState(&iMouseX, &iMouseY);
    int iTileWidth = oWorld->oLevelLayer->fGetSpriteWidth();
    int iTileHeight = oWorld->oLevelLayer->fGetSpriteHeight();
    int iTileCol = fGetTileCol(iMouseX,iTileWidth);
    int iTileRow = fGetTileRow(iMouseY,iTileHeight);
    int iRectX = (iTileCol*iTileWidth);
    int iRectY = (iTileRow*iTileHeight);
    int iXOffset=0,iYOffset=0;


    // Because of the screenscrolling you need to know the offset in pixels before we can exactly calculate on which tile the mouse cursor is. But
    // we dont want to do this when the sprite picker is shown, because that is always statis align from the upper left corner (0,0).
    if (!blSpritePalet)
    {
        iXOffset = (-(oWorld->oCam->X)%iTileWidth);
        iYOffset = (-(oWorld->oCam->Y)%iTileHeight);
    }

    //Recalculate the real tile using the camera offset
    iTileCol = fGetTileCol(iMouseX-oWorld->oCam->X-iXOffset,iTileWidth);
    iTileRow = fGetTileRow(iMouseY-oWorld->oCam->Y-iYOffset,iTileHeight);

    if(blSpritePalet) //The Sprite palet/picker is on screen,
    {
        oWorld->oSpritePicker->fRender(0,0);  //render this at fixed position.
        switch(iMouseButtons)
        {
        case 1:
            //Left button, selects the source sprite
            int iPickedTileCol = fGetTileCol(iMouseX,iTileWidth);
            int iPickedTileRow = fGetTileRow(iMouseY,iTileHeight);
            oWorld->oPencil->iSourceTileRow=iPickedTileRow;
            oWorld->oPencil->iSourceTileCol=iPickedTileCol;

            blSpritePalet=!blSpritePalet; // Hide sprite palet
            blRenderLevel=!blRenderLevel; // Show level again
            break;
        }
    }
    else
    {
        // The is in paint mode
        if((iTileRow<oWorld->oLevelLayer->fGetTotalRows()) && (iTileCol<oWorld->oLevelLayer->fGetTotalCols()) && (iTileRow>-1) && (iTileCol>-1))
        {
            switch(iMouseButtons)
            {
            case 1:
                //Left button, Draw
                oWorld->oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=oWorld->oPencil->iSourceTileCol;
                oWorld->oLevelLayer->p_LevelData[iTileRow][iTileCol].iRow=oWorld->oPencil->iSourceTileRow;
                oWorld->oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=SPRITE;
                break;

            case 4:
                //Right button, Clear
                oWorld->oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=0;
                oWorld->oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=EMPTY;
                break;
            }
        }
    }

    //Draw tile placeholder aka the mouse pointer
    fDrawRectangle(iRectX-iXOffset,iRectY-iYOffset,iTileWidth,iTileHeight,0xFFFFFF);
}

int cGame::fGetTileCol(int iX, int iTileWidth)
{
    return static_cast<int>(floor(iX/iTileWidth));
}
int cGame::fGetTileRow(int iY, int iTileHeight)
{
    return static_cast<int>(floor(iY/iTileHeight));
}

void cGame::fDrawRectangle(int x, int y, int w, int h, Uint32 color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_FillRect(oWorld->sScreenSurface,&rect,color);
}

void cGame::fRender()
{
    /* Create a black background */
    Uint32 color = SDL_MapRGB (oWorld->sScreenSurface->format, 0, 0, 0);
    SDL_FillRect (oWorld->sScreenSurface, NULL, color);

    // Render the background layer
    oWorld->oBackgroundLayer->fRender(0,0,oWorld->oCam->X,oWorld->oCam->Y);

    //Render the level layer
    if(blRenderLevel)
    {
        if(oWorld->oLevelLayer->fIsBuffered())
        {
            // If we are in Edit mode, then force render of the level layer to buffer surface
            if(blEditMode)
            {
                oWorld->oLevelLayer->fClear();
                oWorld->oLevelLayer->fRender(0,0);
            }

            // Blit the buffer surface to the main screen. (TODO: Somehow this just won't work arrghhh...
            SDL_Rect rDest;
            rDest.x = oWorld->oCam->X;
            rDest.y = oWorld->oCam->Y;
            rDest.w = oWorld->oLevelLayer->fGetWidth();
            rDest.h = oWorld->oLevelLayer->fGetWidth();
            SDL_BlitSurface(oWorld->oLevelLayer->fGetBufferSurface(), NULL, oWorld->sScreenSurface, &rDest);
        }
        else
        {
            oWorld->oLevelLayer->fRender(oWorld->oCam->X,oWorld->oCam->Y);
        }

        //Update (and that includes rendering of) all the levelobjects
        list<iLevelObject*>::iterator itObject = oWorld->lLevelObjects.begin();
        for (itObject = oWorld->lLevelObjects.begin(); itObject != oWorld->lLevelObjects.end(); ++itObject) {
            (*itObject)->fUpdate();
        }
    }

    //Overlay
    if(blEditMode)
    {
        fRenderEditMode();
    }

    fRenderUI();

    /* Switch video buffer */
    SDL_Flip (oWorld->sScreenSurface);
}

void cGame::fRenderUI()
{
    itoa(iFPS,chFPS,10);
    oWorld->sTextSurface = TTF_RenderText_Shaded(ttfFont, chFPS, cGreen, cBlack);
    SDL_SetColorKey(oWorld->sTextSurface, SDL_SRCCOLORKEY, SDL_MapRGB(oWorld->sTextSurface->format,  0,  0,  0));
    SDL_BlitSurface(oWorld->sTextSurface, NULL, oWorld->sScreenSurface, &rFPSLocation);
    SDL_FreeSurface(oWorld->sTextSurface);
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
        }
        else    TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 12);
        SDL_Color foregroundColor = { 255, 255, 255 };
        SDL_Color backgroundColor = { 0, 0, 255 };
        SDL_Rect textLocation = { 100, 100, 0, 0 };
        {
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
