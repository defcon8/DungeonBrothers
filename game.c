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
        iPos = -(oPlayerObject->X - (oWorld->oConfig->m_iScreenWidth/2) - oPlayerObject->oPlayerLayer->fGetWidth());
        if(iPos < oCam->X)
        {
            // Let the Camera go left
            oCam->X-=oCam->iVelocityCam;
        }else if(iPos > oCam->X){
            // Let the Camera go left
            oCam->X+=oCam->iVelocityCam;
        }

        //Up/Down
        if(!oPlayerObject->blIsJumping) //Do not update camera on player jump
        {
            iPos = -(oPlayerObject->Y - (oWorld->oConfig->m_iScreenHeight/2) - oPlayerObject->oPlayerLayer->fGetHeight());
            if(iPos < oCam->Y)
            {
                // Let the Camera go up
                oCam->Y--;
            }else if(iPos > oCam->Y){
                // Let the Camera go down
                oCam->Y++;
            }else{
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
    oBackgroundLayer = new cSprite(oWorld->oConfig->m_sScreen, oWorld->oConfig->m_iScreenWidth, oWorld->oConfig->m_iScreenHeight);
    oBackgroundLayer->fLoad("back.bmp");
    oBackgroundLayer->fSetSpriteWidth(6400);
    oBackgroundLayer->fSetSpriteHeight(480);

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
    oLevelLayer = new cSpriteLayer(oWorld->oConfig->m_sScreen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth,false,oWorld->oConfig->m_iScreenWidth,oWorld->oConfig->m_iScreenHeight,true,true,0,0,0);

    //Setup Source
    oLevelLayer->p_Source->fSetSpriteSpacer(iSpriteSpacer);
    oLevelLayer->p_Source->fLoad(chTileSource);
    oLevelLayer->p_Source->fSetSpriteWidthOffset(iSpriteWidthOffset);
    oLevelLayer->p_Source->fSetSpriteHeightOffset(iSpriteHeightOffset);
    oLevelLayer->p_Source->fSetSpriteHeight(iSpriteHeight);
    oLevelLayer->p_Source->fSetSpriteWidth(iSpriteWidth);

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

        oLevelLayer->p_LevelData[iRow][iCol].iType=iType;
        oLevelLayer->p_LevelData[iRow][iCol].iRow=iSheetRow;
        oLevelLayer->p_LevelData[iRow][iCol].iIndex=iSheetIndex;
    }

    oLevelLayer->fRender(0,0); //Because this is a buffered layer, we render it once direct after construction of the data array.

    // ------------ [ start setup camera ] --------------------
    oCam = new cCamera();

    // ------------ [ start setup player ] --------------------

    cPlayer* oPlayer;
    oPlayer = new cPlayer(oWorld->oConfig->m_sScreen,oLevelLayer,oCam, "player.bmp",40,32,oWorld->oConfig->m_iScreenWidth,oWorld->oConfig->m_iScreenHeight);
    lLevelObjects.push_back(oPlayer);    //Add to level object list
    oPlayerObject = oPlayer;             //Store pointer localy, so we can redirect the user input to the object directly without having to search in the levelobject list.

    //Close File
    oLoad.close();

    // ------------ [ start setup spritepicker ] --------------------
    oSpritePicker = new cSpriteLayer(oWorld->oConfig->m_sScreen,iSourceRows,iSourceCols,iSpriteHeight,iSpriteWidth,false,oWorld->oConfig->m_iScreenWidth,oWorld->oConfig->m_iScreenHeight,false,false,0,0,0);
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
    oWorld->oConfig->m_sScreen = SDL_SetVideoMode (oWorld->oConfig->m_iScreenWidth, oWorld->oConfig->m_iScreenHeight, oWorld->oConfig->m_iScreenBits, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

    if (oWorld->oConfig->m_sScreen == NULL)
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
                oPlayerObject->fMoveDirection(1,true);
                break;
            case SDLK_RIGHT:
                oPlayerObject->fMoveDirection(2,true);
                break;
            case SDLK_DOWN :
                oPlayerObject->fMoveDirection(3,true);
                break;
            case SDLK_LEFT:
                oPlayerObject->fMoveDirection(4,true);
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
                if(!oPlayerObject->blIsJumping)
                    oPlayerObject->fJump();
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                {
                    oPlayerObject->fMoveDirection(1,false);
                    break;
                }

                case SDLK_RIGHT:
                {
                    oPlayerObject->fMoveDirection(2,false);
                    break;
                }
                case SDLK_DOWN:
                {
                    oPlayerObject->fMoveDirection(3,false);
                    break;
                }
                case SDLK_LEFT:
                {
                    oPlayerObject->fMoveDirection(4,false);
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
                fSaveLayer(oLevelLayer);
                SDL_WM_SetCaption ("Current Layer Saved.", NULL);
                break;

            case SDLK_F4:
                //Save Demo
                fSaveDemo();
                SDL_WM_SetCaption ("Basic demolevel Saved.", NULL);
                break;

            case SDLK_LEFT:
                oCam->Direction=oCam->left;
                break;

            case SDLK_RIGHT:
                oCam->Direction=oCam->right;
                break;

            case SDLK_UP:
                oCam->Direction=oCam->up;
                break;

            case SDLK_DOWN:
                oCam->Direction=oCam->down;
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
                oCam->Direction=oCam->none;
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
        oCam->X-=iMouseScrollSpeed;
    if(x<(oWorld->oConfig->m_iScreenWidth*(1.0 - dbMouseCornerWidthPerc))) // Invert
        oCam->X+=iMouseScrollSpeed;
    if(y>(oWorld->oConfig->m_iScreenHeight*dbMouseCornerWidthPerc))
        oCam->Y-=iMouseScrollSpeed;
    if(y<(oWorld->oConfig->m_iScreenHeight*(1.0 - dbMouseCornerWidthPerc)))
        oCam->Y+=iMouseScrollSpeed;
}

void cGame::fObjectMovement()
{
    //Do Camera movement
    switch(oCam->Direction)
    {
    case 1:
        oCam->Y += 1;
        break;
    case 2:
        oCam->X -= 1;
        break;
    case 3:
        oCam->Y -= 1;
        break;
    case 4:
        oCam->X += 1;
        break;
    }

    //Scroll Back
    if(iRenderedFrames%5 ==0)
        oBackgroundLayer->fScroll();
}

cGame::cGame()
{
    fInitVariables();
}

void cGame::fInitVariables()
{
    oWorld = new cWorld();

    blDone = false;
    oPencil = new cPencil;
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
    cRed.r=255;
    cRed.g=0;
    cRed.b=0;
    rFPSLocation.x=25;
    rFPSLocation.y=oWorld->oConfig->m_iScreenHeight-25;
}

cGame::~cGame()
{}

void cGame::fCleanUp()
{
    //Destroy objects
    delete oLevelLayer;
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(oWorld->oConfig->m_sScreen);
}

void cGame::fRenderEditMode()
{
    // Get position of mouse and calculate the according position in tiles/rows
    int iMouseX, iMouseY;
    int iMouseButtons = SDL_GetMouseState(&iMouseX, &iMouseY);
    int iTileWidth = oLevelLayer->fGetSpriteWidth();
    int iTileHeight = oLevelLayer->fGetSpriteHeight();
    int iTileCol = fGetTileCol(iMouseX,iTileWidth);
    int iTileRow = fGetTileRow(iMouseY,iTileHeight);
    int iRectX = (iTileCol*iTileWidth);
    int iRectY = (iTileRow*iTileHeight);
    int iXOffset=0,iYOffset=0;


    // Because of the screenscrolling you need to know the offset in pixels before we can exactly calculate on which tile the mouse cursor is. But
    // we dont want to do this when the sprite picker is shown, because that is always statis align from the upper left corner (0,0).
    if (!blSpritePalet)
    {
        iXOffset = (-(oCam->X)%iTileWidth);
        iYOffset = (-(oCam->Y)%iTileHeight);
    }

    //Recalculate the real tile using the camera offset
    iTileCol = fGetTileCol(iMouseX-oCam->X-iXOffset,iTileWidth);
    iTileRow = fGetTileRow(iMouseY-oCam->Y-iYOffset,iTileHeight);

    if(blSpritePalet) //The Sprite palet/picker is on screen,
    {
        oSpritePicker->fRender(0,0);  //render this at fixed position.
        switch(iMouseButtons)
        {
        case 1:
            //Left button, selects the source sprite
            int iPickedTileCol = fGetTileCol(iMouseX,iTileWidth);
            int iPickedTileRow = fGetTileRow(iMouseY,iTileHeight);
            oPencil->iSourceTileRow=iPickedTileRow;
            oPencil->iSourceTileCol=iPickedTileCol;

            blSpritePalet=!blSpritePalet; // Hide sprite palet
            blRenderLevel=!blRenderLevel; // Show level again
            break;
        }
    }
    else
    {
        // The is in paint mode
        if((iTileRow<oLevelLayer->fGetTotalRows()) && (iTileCol<oLevelLayer->fGetTotalCols()) && (iTileRow>-1) && (iTileCol>-1))
        {
            switch(iMouseButtons)
            {
                case 1:
                    //Left button, Draw
                    oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=oPencil->iSourceTileCol;
                    oLevelLayer->p_LevelData[iTileRow][iTileCol].iRow=oPencil->iSourceTileRow;
                    oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=SPRITE;
                    break;

                case 4:
                    //Right button, Clear
                    oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=0;
                    oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=EMPTY;
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
    SDL_FillRect(oWorld->oConfig->m_sScreen,&rect,color);
}

void cGame::fRender()
{
    /* Create a black background */
    SDL_Rect rect;
    Uint32 color;
    color = SDL_MapRGB (oWorld->oConfig->m_sScreen->format, 0, 0, 0);
    SDL_FillRect (oWorld->oConfig->m_sScreen, NULL, color);

    // Render the background layer
    oBackgroundLayer->fRender(0,0,oCam->X,oCam->Y);

    //Render the level layer
    if(blRenderLevel)
    {
        if(oLevelLayer->fIsBuffered())
        {
            // If we are in Edit mode, then force render of the level layer to buffer surface
            if(blEditMode)
            {
                oLevelLayer->fClear();
                oLevelLayer->fRender(0,0);
            }

            // Blit the buffer surface to the main screen. (TODO: Somehow this just won't work arrghhh...
            SDL_Rect destination;
            destination.x = oCam->X;
            destination.y = oCam->Y;
            destination.w = oLevelLayer->fGetWidth();
            destination.h = oLevelLayer->fGetWidth();
            SDL_BlitSurface(oLevelLayer->fGetBufferSurface(), NULL, oWorld->oConfig->m_sScreen, &destination);
        }
        else
        {
            oLevelLayer->fRender(oCam->X,oCam->Y);
        }

        //Update all the levelobjects
        list<iLevelObject*>::iterator p = lLevelObjects.begin();
        (*p)->fUpdate();


    }

    //Overlay
    if(blEditMode)
    {
        fRenderEditMode();
    }

    fRenderUI();

    /* Switch video buffer */
    SDL_Flip (oWorld->oConfig->m_sScreen);
}

void cGame::fRenderUI()
{
    itoa(iFPS,chFPS,10);
    textSurface = TTF_RenderText_Shaded(ttfFont, chFPS, cRed, cBlack);
    SDL_BlitSurface(textSurface, NULL, oWorld->oConfig->m_sScreen, &rFPSLocation);
    SDL_FreeSurface(textSurface);
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
