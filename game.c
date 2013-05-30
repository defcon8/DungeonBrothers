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
    // TODO
//    //Scroll to the right
//    if(oPlayerLayer->x<(-CamX))
//            CamX+=200;
//
//
//    //Scroll to the right
//    if(oPlayerLayer->x>((-CamX)+iScreenWidth))
//            CamX-=200;

}

void cGame::Start()
{
    fInitialize();
    fLoadObjects();

    while(!blDone)
    {
        fEvents();
        fObjectMovement();
        fCameraMovement();
        fGameLoop();
        fRender();
        //Todo: Cap to FPS
        //SDL_Delay(1);
    }

    fCleanUp();
}

void cGame::fLoadObjects()
{
    //Background Layer
    oBackgroundLayer = new cSprite(screen);
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
    oLevelLayer = new cSpriteLayer(screen,iLevelRows,iLevelCols,iSpriteHeight,iSpriteWidth,false,iScreenWidth,iScreenHeight,true,true,0,0,0);

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
    oPlayer = new cPlayer(screen,oLevelLayer,oCam, chTileSource,32,32,iScreenWidth,iScreenHeight);
    lLevelObjects.push_back(oPlayer);    //Add to level object list
    oPlayerObject = oPlayer;             //Store pointer localy, so we can redirect the user input to the object directly without having to search in the levelobject list.

    //Close File
    oLoad.close();

    // ------------ [ start setup spritepicker ] --------------------
    oSpritePicker = new cSpriteLayer(screen,iSourceRows,iSourceCols,iSpriteHeight,iSpriteWidth,false,iScreenWidth,iScreenHeight,false,false,0,0,0);
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

//    /**< Test: Gravity, should be 10.000x better designed */
//    if((!iPlayerDirection==UP) && (!fCheckDirectionCollision(oPlayerLayer,DOWN)))
//    {
//     oPlayerLayer->y=oPlayerLayer->y++;
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

    atexit (SDL_Quit);
    screen = SDL_SetVideoMode (iScreenWidth, iScreenHeight, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (screen == NULL)
    {
        sprintf (chMessage, "Couldn't set video mode: %s\n",
                 SDL_GetError ());
        MessageBox (0, chMessage, "Error", MB_ICONHAND);
        free(chMessage);
        exit(2);
    }

    SDL_WM_SetCaption ("Dungeon Brothers ALPHA", NULL);
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
                }
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
                SDL_WM_SetCaption ("Layer Saved.", NULL);
                break;

            case SDLK_F4:
                //Save Demo
                fSaveDemo();
                SDL_WM_SetCaption ("Demolevel Saved.", NULL);
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
    if(x>(iScreenWidth*dbMouseCornerWidthPerc))
        oCam->X-=iMouseScrollSpeed;
    if(x<(iScreenWidth*(1.0 - dbMouseCornerWidthPerc))) // Invert
        oCam->X+=iMouseScrollSpeed;
    if(y>(iScreenHeight*dbMouseCornerWidthPerc))
        oCam->Y-=iMouseScrollSpeed;
    if(y<(iScreenHeight*(1.0 - dbMouseCornerWidthPerc)))
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
}

cGame::cGame(int iScrWidth, int iScrHeight)
{
    fInitVariables(iScrWidth, iScrHeight);
}

void cGame::fInitVariables(int iScrWidth, int iScrHeight)
{
    blDone = false;
    iScreenWidth=iScrWidth;
    iScreenHeight=iScrHeight;
    blEditMode = false;
    blRenderLevel = true;
    blSpritePalet = false;
    MouseX=0;
    MouseY=0;
    dbMouseCornerWidthPerc=0.95;
    iMouseScrollSpeed=5;
    oPencil = new cPencil;
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

    //Recalculate the real tile using the camera offset
    iTileCol = fGetTileCol(x-oCam->X,iTileWidth);
    iTileRow = fGetTileRow(y-oCam->Y,iTileHeight);

    if(blSpritePalet)
    {
        oSpritePicker->fRender(oCam->X,oCam->Y);
        //The Sprite palet/picker is on screen
        switch(iMouseButtons)
        {
        case 1:
            //Left button, selects the source sprite
            oPencil->iSourceTileRow=iTileRow;
            oPencil->iSourceTileCol=iTileCol;
            blSpritePalet=!blSpritePalet; // Hide sprite palet
            blRenderLevel=!blRenderLevel; // Show level again

            oLevelLayer->p_LevelData[iTileRow][iTileCol].iIndex=2;
            oLevelLayer->p_LevelData[iTileRow][iTileCol].iType=SPRITE;
            break;
        }
    }
    else
    {
        // The is in paint mode
        if((iTileRow<oLevelLayer->fGetTotalRows()) && (iTileCol<oLevelLayer->fGetTotalCols()) &&
                (iTileRow>-1) && (iTileCol>-1))
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

    //Draw tile placeholder aka mouse pointer
    fDrawRectangle(iRectX,iRectY,iTileWidth,iTileHeight,0xFFFFFF);
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
    SDL_FillRect(screen,&rect,color);
}

void cGame::fRender()
{
    /* Create a black background */
    SDL_Rect rect;
    Uint32 color;
    color = SDL_MapRGB (screen->format, 0, 0, 0);
    SDL_FillRect (screen, NULL, color);

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
            SDL_BlitSurface(oLevelLayer->fGetBufferSurface(), NULL, screen, &destination);
        }else{
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

    /* Switch video buffer */
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
        }
        else
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
