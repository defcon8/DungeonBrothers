#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "config.h"
#include "debug.h"
#include "pencil.h"
#include "spritelayer.h"
#include "player.h"
#include "physics.h"
#include "menu.h"
#include "camera.h"
#include "ilevelobject.h"
#include "levelobject.h"

#define MODE_GAME 0
#define MODE_MENU 1
#define MODE_EDIT 2

using namespace std;

class cWorld {

public:

    int gamemode;

    cConfig* config;
    cPencil* pencil;
    cSpriteLayer* levellayer;
    cSpriteLayer* spritepicker;
    cSprite* backgroundlayer;
    cPlayer* playerobject;
    cCamera* cam;
    cPhysics* physics;
    cMenu* menu;

    SDL_Surface *screensurface;
    SDL_Surface *virtualsurface;
    SDL_Surface *textsurface;

    list<iLevelObject*> levelobjects;

    cWorld();
    ~cWorld();




protected:
private:
};

#endif // WORLD_H
