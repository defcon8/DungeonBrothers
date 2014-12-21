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
#include "..\include\game.h"

using namespace std;

void cGame::saveLayer(cSpriteLayer *spritelayer)
{
    ofstream save;
    save.open ("spritelayer.dat",ios::binary);

    //Header
    char tilesource[16];
    memcpy(&tilesource[0],spritelayer->source->getTileSource(),16);

    Uint16 levelrows = spritelayer->getTotalRows();
    Uint16 levelcols = spritelayer->getTotalCols();
    Uint16 spriteheight = spritelayer->getSpriteHeight();
    Uint16 spritewidth = spritelayer->getSpriteWidth();;
    Uint16 sourcerows=11;
    Uint16 sourcecols=18;
    Uint8 spritespacer=2;
    Uint8 spritewidthoffset=0;
    Uint8 spriteheightoffset=0;
    Uint16 datablocks=(levelrows*levelcols); // Count the nr of blocks

    save.write((char*)&tilesource,sizeof(tilesource));
    save.write((char*)&levelrows,sizeof(Uint16));
    save.write((char*)&levelcols,sizeof(Uint16));
    save.write((char*)&spriteheight,sizeof(Uint16));
    save.write((char*)&spritewidth,sizeof(Uint16));
    save.write((char*)&sourcerows,sizeof(Uint16));
    save.write((char*)&sourcecols,sizeof(Uint16));
    save.write((char*)&spritespacer,sizeof(Uint8));
    save.write((char*)&spritewidthoffset,sizeof(Uint8));
    save.write((char*)&spriteheightoffset,sizeof(Uint8));
    save.write((char*)&datablocks,sizeof(Uint16));

    // DataBlocks
    for (int row = 0; row <= (levelrows-1)  ; row++ ) {
        for (int col = 0; col <= (levelcols-1) ; col++ ) {
            Uint8 type=spritelayer->leveldata[row][col].type;
            Uint8 sheetrow=spritelayer->leveldata[row][col].row;
            Uint8 sheetindex=spritelayer->leveldata[row][col].index;

            save.write((char*)&row,sizeof(Uint8));
            save.write((char*)&col,sizeof(Uint8));
            save.write((char*)&type,sizeof(Uint8));
            save.write((char*)&sheetrow,sizeof(Uint8));
            save.write((char*)&sheetindex,sizeof(Uint8));
        }
    }
    save.close();
}

void cGame::saveDemo()
{

    ofstream save;
    save.open ("spritelayer.dat",ios::binary);

    //Header
    char tilesource[16]="blocks1.bmp";
    Uint16 levelrows=15; //15 is 1 full screen at 640x480
    Uint16 levelcols=40; //20 is 1 full screen at 640x480
    Uint16 spriteheight=32;
    Uint16 spritewidth=32;
    Uint16 sourcerows=11;
    Uint16 sourcecols=18;
    Uint8 spritespacer=2;
    Uint8 spritewidthoffset=0;
    Uint8 spriteheightoffset=0;
    Uint16 datablocks=40;

    save.write((char*)&tilesource,sizeof(tilesource));
    save.write((char*)&levelrows,sizeof(Uint16));
    save.write((char*)&levelcols,sizeof(Uint16));
    save.write((char*)&spriteheight,sizeof(Uint16));
    save.write((char*)&spritewidth,sizeof(Uint16));
    save.write((char*)&sourcerows,sizeof(Uint16));
    save.write((char*)&sourcecols,sizeof(Uint16));
    save.write((char*)&spritespacer,sizeof(Uint8));
    save.write((char*)&spritewidthoffset,sizeof(Uint8));
    save.write((char*)&spriteheightoffset,sizeof(Uint8));
    save.write((char*)&datablocks,sizeof(Uint16));

    // DataBlocks
    for (int sprite = 0; sprite < datablocks; sprite++) {
        // Test Fill
        Uint8 row=14;
        Uint8 col=sprite;
        Uint8 type=1;
        Uint8 sheetrow=1;
        Uint8 sheetindex=6;
        // End Test Fill

        save.write((char*)&row,sizeof(Uint8));
        save.write((char*)&col,sizeof(Uint8));
        save.write((char*)&type,sizeof(Uint8));
        save.write((char*)&sheetrow,sizeof(Uint8));
        save.write((char*)&sheetindex,sizeof(Uint8));
    }

    save.close();
}

void cGame::functionTests()
{
    cSpriteLayer* temp = new cSpriteLayer(world,10,10,32,32,true,true,false,0,0,0);

    if(temp->yToRow(0) != 0) {
        TRACE("Init","fYToRow(0) FAIL!");
    }

    if(temp->yToRow(32) != 1) {
        TRACE("Init","fYToRow() FAIL!");
    }

    if(temp->xToCol(0) != 0) {
        TRACE("Init","fYToRow(0) FAIL!");
    }

    if(temp->xToCol(32) != 1) {
        TRACE("Init","fXToCol() FAIL!");
    }


}

void cGame::start()
{
    initialize();

    functionTests();

    intro();

    loadObjects();

    while(!done) {
        long measure1 = time(NULL);
        events();
        objectMovement();
        gameLoop();
        render();
        renderedframes++;
        calcfps();
        long measure2 = time(NULL); //Give system time to the OS, prevent 100% Core usage.
        long diff = measure2 - measure1;
        SDL_Delay(10- diff); // sleep until next tick : BW SHOULD BE 13
    }
    cleanUp();
}

void cGame::calcfps()
{
    elapsedseconds=time(NULL)-starttime;
    if(elapsedseconds>0) //Protect against divide by zero, crash at program startup.
        fps=renderedframes/elapsedseconds;
}

void cGame::loadObjects()
{
    TRACE("Init","Loading objects");

    //Background Layer
    world->backgroundlayer = new cSprite(world);
    world->backgroundlayer->load("back.bmp");
    world->backgroundlayer->spritewidth = 6400;
    world->backgroundlayer->spriteheight = 480;

    //Level Layer
    char tilesource[16];
    Uint16 levelrows;
    Uint16 levelcols;
    Uint16 spriteheight;
    Uint16 spritewidth;
    Uint16 sourcerows;
    Uint16 sourcecols;
    Uint8 spritespacer;
    Uint8 spritewidthoffset;
    Uint8 spriteheightoffset;
    Uint16 datablocks;

    std::ifstream load;
    load.open("spritelayer.dat", ios_base::in | ios_base::binary);

    load.read(reinterpret_cast<char*>(&tilesource),sizeof(tilesource));
    load.read(reinterpret_cast<char*>(&levelrows),sizeof(Uint16));
    load.read(reinterpret_cast<char*>(&levelcols),sizeof(Uint16));
    load.read(reinterpret_cast<char*>(&spriteheight),sizeof(Uint16));
    load.read(reinterpret_cast<char*>(&spritewidth),sizeof(Uint16));
    load.read(reinterpret_cast<char*>(&sourcerows),sizeof(Uint16));
    load.read(reinterpret_cast<char*>(&sourcecols),sizeof(Uint16));
    load.read(reinterpret_cast<char*>(&spritespacer),sizeof(Uint8));
    load.read(reinterpret_cast<char*>(&spritewidthoffset),sizeof(Uint8));
    load.read(reinterpret_cast<char*>(&spriteheightoffset),sizeof(Uint8));
    load.read(reinterpret_cast<char*>(&datablocks),sizeof(Uint16));

    TRACE("Init","Load > spritespacer: %d",spritespacer);
    TRACE("Init","Load > spriteheightoffset: %d",spriteheightoffset);
    TRACE("Init","Load > spritewidthoffset: %d",spritewidthoffset);


    // ------------ [ start setup level ] --------------------
    world->levellayer = new cSpriteLayer(world, levelrows, levelcols, spriteheight, spritewidth,false,true,true,0,0,0);

    //Setup Source
    world->levellayer->source->spritespacer = spritespacer;
    world->levellayer->source->load(tilesource);
    world->levellayer->source->spritewidthoffset = spritewidthoffset;
    world->levellayer->source->spriteheightoffset = spriteheightoffset;
    world->levellayer->source->spriteheight = spriteheight;
    world->levellayer->source->spritewidth = spritewidth;

    // Get Slopes
    bool dummy = world->levellayer->source->getSlopes();

    // Read DataBlocks from file
    for (int sprite = 0; sprite < datablocks; sprite++) {
        Uint8 row;
        Uint8 col;
        Uint8 type;
        Uint8 sheetrow;
        Uint8 sheetindex;

        load.read(reinterpret_cast<char*>(&row),sizeof(Uint8));
        load.read(reinterpret_cast<char*>(&col),sizeof(Uint8));
        load.read(reinterpret_cast<char*>(&type),sizeof(Uint8));
        load.read(reinterpret_cast<char*>(&sheetrow),sizeof(Uint8));
        load.read(reinterpret_cast<char*>(&sheetindex),sizeof(Uint8));

        world->levellayer->leveldata[row][col].type=type;
        world->levellayer->leveldata[row][col].row=sheetrow;
        world->levellayer->leveldata[row][col].index=sheetindex;
    }

    world->levellayer->render(0,0); //Because this is a buffered layer, we render it once direct after construction of the data array.

    // ------------ [ start setup player ] --------------------

    char playerbitmap[]="player.bmp";
    world->playerobject = new cPlayer(world, playerbitmap,40,32);
    world->levelobjects.push_back(world->playerobject);    //Add to level object list

    // Close File
    load.close();

    // ------------ [ start setup spritepicker ] --------------------
    world->spritepicker = new cSpriteLayer(world, sourcerows, sourcecols, spriteheight, spritewidth,false,false,false,0,0,0);
    world->spritepicker->source->spritespacer = 2;
    world->spritepicker->source->load(tilesource);
    world->spritepicker->source->spritewidthoffset = 0;
    world->spritepicker->source->spriteheightoffset = 0;
    world->spritepicker->source->spriteheight = spriteheight;
    world->spritepicker->source->spritewidth = spritewidth;

    for (int col = 0; col < sourcecols; col++) {
        for (int row = 0; row < sourcerows; row++) {
            world->spritepicker->leveldata[row][col].type=SPRITE;
            world->spritepicker->leveldata[row][col].row=row;
            world->spritepicker->leveldata[row][col].index=col;
        }
    }
}

void cGame::gameLoop()
{
    // Game Logic

}

void cGame::initialize()
{
    //For debugging purposes (BW: TODO -> Does not work!)
    TRACE("Init","Initializing..");

    /* Initialize SDL */
    char *message;
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        sprintf (message, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        MessageBox (0, message, "Error", MB_ICONHAND);
        free(message);
        exit(1);
    }

    TTF_Init();
    ttffont = TTF_OpenFont("Fonts\\BeckerBlackNF.ttf", 20);

    if (ttffont == NULL) {
        sprintf (message, "Can't load font.");
        SDL_GetError ();
        MessageBox(0,message,"Error",MB_ICONHAND);
        free(message);
        exit(2);
    }

    atexit (SDL_Quit);
    world->screensurface = SDL_SetVideoMode(world->config->screenwidth, world->config->screenheight, world->config->screenbits, world->config->SDLflags);


    if (world->screensurface == NULL) {
        sprintf (message, "Couldn't set video mode: %s\n", SDL_GetError ());
        MessageBox (0, message, "Error", MB_ICONHAND);
        free(message);
        exit(2);
    }

    // this is the virtual surface we are drawing on.
    world->virtualsurface = SDL_CreateRGBSurface(SDL_SWSURFACE,(world->config->virtualresolution ? 640 : world->config->screenwidth),(world->config->virtualresolution ? 480 : world->config->screenheight),
                            world->screensurface->format->BitsPerPixel,
                            world->screensurface->format->Rmask,
                            world->screensurface->format->Gmask,
                            world->screensurface->format->Bmask,
                            world->screensurface->format->Amask);

    SDL_WM_SetCaption ("Dungeon Brothers", NULL);
    SDL_ShowCursor(SDL_DISABLE);

}

void cGame::events()
{
    SDL_Event event;

    //Todo:
    //Shared mode key events?

    switch(world->gamemode) {
    case MODE_MENU:
        menuModeEvents(&event);
        break;
    case MODE_GAME:
        gameModeEvents(&event);
        break;
    case MODE_EDIT:
        editModeEvents(&event);
        break;
    }
}

void cGame::menuModeEvents(SDL_Event *event)
{
    while (SDL_PollEvent (event)) {
        switch (event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
            case SDLK_ESCAPE:
                TRACE("Events","Keydown ESCAPE | Enter game mode");
                world->gamemode = MODE_GAME;
                renderlevel = true;
                break;
            case SDLK_x:
                done = true;
                break;
            case SDLK_RETURN:
                selectMenuItem();
                break;
            case SDLK_UP:
                TRACE("Events","menu Up");
                if(world->menu->menupath.size() == 0) {
                    //main menu
                    selectedmenuitem = (selectedmenuitem > 0 ? selectedmenuitem-1 : (world->menu->menuitems.size()-1));
                } else {
                    // sub menu
                    selectedmenuitem = (selectedmenuitem > 0 ? selectedmenuitem-1 : (world->menu->menupath.back().menuitems.size()-1));
                }
                break;
            case SDLK_DOWN:
                TRACE("Events","Menu Down");
                if(world->menu->menupath.size() == 0) {
                    //main menu
                    selectedmenuitem = (selectedmenuitem < (world->menu->menuitems.size()-1) ? selectedmenuitem+1 : 0);
                } else {
                    // sub menu
                    selectedmenuitem = (selectedmenuitem < (world->menu->menupath.back().menuitems.size()-1) ? selectedmenuitem+1 : 0);
                }
                break;
            }
            break;
        case SDL_QUIT:
            TRACE("Events","Received SDL_WINDOWEVENT_CLOSED");
            done = true;
            break;
        default:
            break;
        }
    }
}

void cGame::gameModeEvents(SDL_Event *event)
{
    while (SDL_PollEvent (event)) {
        switch (event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
            case SDLK_UP:
                TRACE("Events","Keydown UP");
                world->playerobject->moveDirection(1,true);
                break;
            case SDLK_RIGHT:
                TRACE("Events","Keydown RIGHT");
                world->playerobject->moveDirection(2,true);
                break;
            case SDLK_DOWN :
                TRACE("Events","Keydown DOWN");
                world->playerobject->moveDirection(3,true);
                break;
            case SDLK_LEFT:
                TRACE("Events","Keydown LEFT");
                world->playerobject->moveDirection(4,true);
                break;
            case SDLK_ESCAPE:
                TRACE("Events","Keydown ESCAPE | Enter menu mode");
                //Show menu
                world->gamemode = MODE_MENU;
                renderlevel = false;
                //blDone=true;
                //blEditMode = true;
                break;
            case SDLK_F1:
                TRACE("Events","Keydown F1 | Enter edit mode");
                TRACE("Mode","Edit mode");
                world->gamemode = MODE_EDIT;
                break;
            case SDLK_SPACE:
                if(!world->playerobject->isjumping)
                    world->playerobject->jump();
                TRACE("Events","Keydown SPACE");
                break;
            case SDLK_RALT:
                world->playerobject->fire();
                TRACE("Events","Keydown R-ALT");
                break;
            case SDLK_x:
                done = true;
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event->key.keysym.sym) {
            case SDLK_UP: {
                world->playerobject->moveDirection(1,false);
                TRACE("Events","Keyup UP");
                break;
            }

            case SDLK_RIGHT: {
                world->playerobject->moveDirection(2,false);
                TRACE("Events","Keyup RIGHT");
                break;
            }
            case SDLK_DOWN: {
                world->playerobject->moveDirection(3,false);
                TRACE("Events","Keyup DOWN");
                break;
            }
            case SDLK_LEFT: {
                world->playerobject->moveDirection(4,false);
                TRACE("Events","Keyup LEFT");
                break;
            }
            }
            break;
        case SDL_QUIT:
            TRACE("Events","Received SDL_WINDOWEVENT_CLOSED");
            done = true;
            break;
        default:
            break;
        }
    }
}

void cGame::editModeEvents(SDL_Event *event)
{
    while (SDL_PollEvent (event)) {
        switch (event->type) {
        case SDL_KEYDOWN:
            switch(event->key.keysym.sym) {
            case SDLK_ESCAPE:
                TRACE("Events","Keydown ESCAPE | Enter game mode");
                TRACE("Mode","Game mode");
                //Show Menu
                world->gamemode = MODE_GAME;
                break;
            case SDLK_x:
                done = true;
                break;
            case SDLK_F1:
                //Toggle Edit mode
                TRACE("Events","Keydown F1 | Enter game mode");
                TRACE("Mode","Game mode");
                world->gamemode = MODE_GAME;
                spritepalet = false;    // Hide SpritePicker
                renderlevel = true;     // Show Level
                break;
            case SDLK_F2:
                //Toggle Sprite Picker
                if(spritepalet) {
                    spritepalet = false;  // Hide Sprite Picker
                    renderlevel = true;   // Hide Level
                    SDL_WM_SetCaption ("Edit mode - Level editor", NULL);
                } else {
                    spritepalet = true;  // Hide Sprite Picker
                    renderlevel = false;   // Hide Level
                    SDL_WM_SetCaption ("Edit mode - Level editor", NULL);
                }
                break;

            case SDLK_F3:
                //Save Layer to File
                saveLayer(world->levellayer);
                SDL_WM_SetCaption ("Current Layer Saved.", NULL);
                break;
            case SDLK_F4:
                //Save Demo
                saveDemo();
                SDL_WM_SetCaption ("Basic demolevel Saved.", NULL);
                break;
            case SDLK_LEFT:
                world->cam->direction = world->cam->left;
                break;
            case SDLK_RIGHT:
                world->cam->direction = world->cam->right;
                break;
            case SDLK_UP:
                world->cam->direction = world->cam->up;
                break;
            case SDLK_DOWN:
                world->cam->direction = world->cam->down;
                break;
            }
            break;
        case SDL_KEYUP:
            switch(event->key.keysym.sym) {
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_UP:
            case SDLK_DOWN:
                world->cam->direction = world->cam->none;
                break;
            }
            break;
        case SDL_QUIT:
            done = 1;
            break;
        default:
            break;
        }
    }

    //Camera movement by mouse corners to navigate thru the scene
//    int x,y;
//    SDL_GetMouseState(&x, &y);
//    if(x>(world->config->screenwidth * mousecornerwidthperc))
//        world->cam->x -= mousescrollspeed;
//    if(x<(world->config->screenwidth*(1.0 - mousecornerwidthperc))) // Invert
//        world->cam->x += mousescrollspeed;
//    if(y>(world->config->screenheight * mousecornerwidthperc))
//        world->cam->y -= mousescrollspeed;
//    if(y<(world->config->screenheight*(1.0 - mousecornerwidthperc)))
//        world->cam->y += mousescrollspeed;
}

void cGame::objectMovement()
{
    world->cam->cameraMovement();
}

cGame::cGame()
{
    world = new cWorld();
    initVariables();
}


void cGame::scaleSurface(SDL_Surface *src, SDL_Surface *dest)
{
    double  _stretch_factor_x = (static_cast<double>(dest->w)  / static_cast<double>(src->w)),
            _stretch_factor_y = (static_cast<double>(dest->h) / static_cast<double>(src->h));

    for(Sint32 y = 0; y < src->h; y++)
        for(Sint32 x = 0; x < src->w; x++)
            for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    drawPixel(dest, static_cast<Sint32>(_stretch_factor_x * x) + o_x, static_cast<Sint32>(_stretch_factor_y * y) + o_y, readPixel(src, x, y));
}


void cGame::initAudio(){
    Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096);
    Mix_Music *music = NULL;
    string filename("Audio\\Theme.wav");
    TRACE("Audio","Load file: %s", filename.c_str());
    music = Mix_LoadMUS(filename.c_str());
    if(music == NULL) {
        TRACE("Audio","Unable to load music file: %s\n", Mix_GetError());
    } else {
        TRACE("Audio","INIT OK!");
    }

    Mix_PlayMusic(music,-1);
}

void cGame::intro()
{
    initAudio();

    SDL_Surface *image;	//This pointer will reference our bitmap sprite
    SDL_Surface *temp;	//This pointer will temporarily reference our bitmap sprite
    SDL_Rect src, dest;	//These rectangles will describe the source and destination regions of our blit

    string filename("GFX\\intro.bmp");

    temp = SDL_LoadBMP(filename.c_str());
    image = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    SDL_BlitSurface(image, NULL, world->virtualsurface, NULL);
    SDL_BlitSurface(world->virtualsurface, NULL, world->screensurface, NULL); // TODO: needs to rescale also
    SDL_Flip(world->screensurface);

    bool done;
    SDL_Delay(2000);

}

void cGame::initVariables()
{
    world->gamemode = MODE_MENU;
    done = false;
    renderlevel = false;
    spritepalet = false;
    mousex=0;
    mousey=0;
    mousecornerwidthperc=0.95;
    mousescrollspeed=5;
    elapsedseconds=0;
    optimalfrequency=30; // FPS
    starttime=time(NULL);
    renderedframes=0;
    fps=0;
    scrolloffset=0;
    selectedmenuitem=0;
    black.r=0;
    black.g=0;
    black.b=0;
    green.r=0;
    green.g=255;
    green.b=0;
    yellow.r=255;
    yellow.g=255;
    yellow.b=0;
    fpslocation.x=30;
    fpslocation.y = world->config->screenheight-50;
}

cGame::~cGame()
{}

void cGame::cleanUp()
{
    SDL_Quit();
    TRACE("Init", "User request application exit.");
}

void cGame::renderEditMode()
{
    // Get position of mouse and calculate the according position in tiles/rows
    int mousex, mousey;
    int mousebuttons = SDL_GetMouseState(&mousex, &mousey);
    int tilewidth = world->levellayer->getSpriteWidth();
    int tileheight = world->levellayer->getSpriteHeight();
    int tilecol = getTileCol(mousex,tilewidth);
    int tilerow = getTileRow(mousey,tileheight);
    int rectx = (tilecol*tilewidth);
    int recty = (tilerow*tileheight);
    int xoffset=0,yoffset=0;

    // Because of the screenscrolling you need to know the offset in pixels before we can exactly calculate on which tile the mouse cursor is. But
    // we dont want to do this when the sprite picker is shown, because that is always statis align from the upper left corner (0,0).
    if (!spritepalet) {
        xoffset = (-(world->cam->x)%tilewidth);
        yoffset = (-(world->cam->y)%tileheight);
    }

    //Recalculate the real tile using the camera offset
    tilecol = getTileCol(mousex-world->cam->x-xoffset,tilewidth);
    tilerow = getTileRow(mousey-world->cam->y-yoffset,tileheight);

    if(spritepalet) { //The Sprite palet/picker is on screen,
        world->spritepicker->render(0,0);  //render this at fixed position.
        switch(mousebuttons) {
        case 1:
            //Left button, selects the source sprite
            int pickedtilecol = getTileCol(mousex,tilewidth);
            int pickedtilerow = getTileRow(mousey,tileheight);
            world->pencil->sourcetilerow = pickedtilerow;
            world->pencil->sourcetilecol = pickedtilecol;

            spritepalet = !spritepalet; // Hide sprite palet
            renderlevel = !renderlevel; // Show level again
            break;
        }
    } else {
        // The is in paint mode
        if((tilerow < world->levellayer->getTotalRows()) && (tilecol < world->levellayer->getTotalCols()) && (tilerow > -1) && (tilecol > -1)) {
            switch(mousebuttons) {
            case 1:
                //Left button, Draw
                world->levellayer->leveldata[tilerow][tilecol].index = world->pencil->sourcetilecol;
                world->levellayer->leveldata[tilerow][tilecol].row = world->pencil->sourcetilerow;
                world->levellayer->leveldata[tilerow][tilecol].type = SPRITE;
                break;

            case 4:
                //Right button, Clear
                world->levellayer->leveldata[tilerow][tilecol].index=0;
                world->levellayer->leveldata[tilerow][tilecol].type=EMPTY;
                break;
            }
        }
    }

    //Draw tile placeholder aka the mouse pointer
    drawRectangle(rectx-xoffset, recty-yoffset, tilewidth, tileheight, 0xFFFFFF);
}

void cGame::selectMenuItem()
{
    //see if the selected menu item has submenuitems
    vector<cMenuItem> *menuitems;
    bool atrootlevel=true;
    //Is the the viewer in topmenu level?
    if(world->menu->menupath.size() == 0) {
        menuitems = &world->menu->menuitems;
    } else {
        menuitems = &world->menu->menupath.front().menuitems;
        atrootlevel=false;
    }

    TRACE("Menu","Selected: %s",menuitems->at(selectedmenuitem).name.c_str());

    int submenuitems = menuitems->at(selectedmenuitem).menuitems.size();
    TRACE("Menu","Subitems: %d",submenuitems);

    if(submenuitems > 0) {
        world->menu->menupath.push_back(menuitems->at(selectedmenuitem));
        selectedmenuitem = 0; //Reset to top item
    } else {
        //Do action for this menu item.
        if(!atrootlevel && (selectedmenuitem==0)) {
            // Go up one menu level
            world->menu->menupath.pop_back();
            return;
        } else {
            menuActionDispatcher(menuitems->at(selectedmenuitem).actionid);
        }
    }
}

void cGame::menuActionDispatcher(int id)
{
    TRACE("Menu","menuActionDispatcher: %d",id);
    switch(id) {
    case 0:
        world->gamemode = MODE_GAME;
        renderlevel = true;
        break;
    case 100:
        world->gamemode = MODE_EDIT;
        renderlevel = true;
        break;
    case 300:
        menuActionExit();
        break;
    }
}

void cGame::menuActionExit()
{
    done=true;
}

void cGame::renderMenuMode()
{

    vector<cMenuItem> *menuitems;
    //Is the the viewer in topmenu level?
    if(world->menu->menupath.size() == 0) {
        menuitems = &world->menu->menuitems;
    } else {
        menuitems = &world->menu->menupath.front().menuitems;
    }


    int item=0;
    for (std::vector<cMenuItem>::iterator it = menuitems->begin(); it != menuitems->end(); it++) {
        SDL_Rect itemlocation;
        itemlocation.w = 200;
        itemlocation.h = 50;
        itemlocation.x = 200;
        itemlocation.y = 200+(item*25);

        SDL_Color itemcolor = (item == selectedmenuitem ? yellow : green);

        world->textsurface = TTF_RenderText_Shaded(ttffont, it->name.c_str(), itemcolor, black);
        SDL_SetColorKey(world->textsurface, SDL_SRCCOLORKEY, SDL_MapRGB(world->textsurface->format,  0,  0,  0));
        SDL_BlitSurface(world->textsurface, NULL, world->virtualsurface, &itemlocation);
        SDL_FreeSurface(world->textsurface);
        item++;
    }
}


int cGame::getTileCol(int x, int tilewidth)
{
    return static_cast<int>(floor(x/tilewidth));
}
int cGame::getTileRow(int y, int tileheight)
{
    return static_cast<int>(floor(y/tileheight));
}

void cGame::drawRectangle(int x, int y, int w, int h, Uint32 color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_FillRect(world->virtualsurface,&rect,color);
}

void cGame::render()
{
    /* Create a black background */
    Uint32 color = SDL_MapRGB (world->virtualsurface->format, 0, 0, 0);
    SDL_FillRect (world->virtualsurface, NULL, color);

    //Render the level layer
    if(renderlevel) {

        // Render the background layer
        world->backgroundlayer->render(0,0,world->cam->x + scrolloffset, world->cam->y);

        if(world->levellayer->isBuffered()) {
            // If we are in Edit mode, then force render of the level layer to buffer surface
            if(world->gamemode == MODE_EDIT) {
                world->levellayer->clearlayer();
                world->levellayer->render(0,0);
            }

            // Blit the buffer surface to the main screen. (TODO: Somehow this just won't work arrghhh...
            SDL_Rect dest;
            dest.x = world->cam->x;
            dest.y = world->cam->y;
            dest.w = world->levellayer->getWidth();
            dest.h = world->levellayer->getWidth();
            SDL_BlitSurface(world->levellayer->getBufferSurface(), NULL, world->virtualsurface, &dest);
        } else {
            world->levellayer->render(world->cam->x, world->cam->y);
        }

        //Update (and that includes rendering of) all the levelobjects
        list<iLevelObject*>::iterator object = world->levelobjects.begin();
        for (object = world->levelobjects.begin(); object != world->levelobjects.end();) {
            if(!(*object)->isAlive()) {
                //Object is dead, remove from list and delete object from memory
                object = world->levelobjects.erase(object);
                //delete (*itObject); //TODO: I think i created a memory leak here, i thought i must delete the object but i cant, somehow my memory doenst seems to grow now.
            } else {
                updateLevelObject(*object);
                ++object;
            }
        }
    }

    //Overlay
    if(world->gamemode == MODE_EDIT) {
        renderEditMode();
    }

    if(world->gamemode == MODE_MENU) {
        renderMenuMode();
    }

    if(world->gamemode == MODE_GAME)
        renderUI();


    if(world->config->virtualresolution) {
        scaleSurface(world->virtualsurface,world->screensurface);
    } else {
        int blitresult = SDL_BlitSurface(world->virtualsurface,NULL,world->screensurface,NULL);
        TRACE("Render","BLIT Result: %d", blitresult);
    }
    /* Switch video buffer */
    SDL_Flip (world->screensurface);
}

void cGame::updateLevelObject(iLevelObject* levelobject)
{
    levelobject->update();
}

void cGame::renderUI()
{
    itoa(fps,fpstext,10);
    world->textsurface = TTF_RenderText_Shaded(ttffont, fpstext, green, black);
    SDL_SetColorKey(world->textsurface, SDL_SRCCOLORKEY, SDL_MapRGB(world->textsurface->format,  0,  0,  0));
    SDL_BlitSurface(world->textsurface, NULL, world->virtualsurface, &fpslocation);
    SDL_FreeSurface(world->textsurface);
}

Uint32 cGame::readPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void cGame::drawPixel(SDL_Surface *screen, int x, int y, Uint32 color)
{
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


void cGame::drawPixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    Uint32 color = SDL_MapRGB(screen->format, r, g, b);
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
