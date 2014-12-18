#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "config.h"
#include "debug.h"
#include "pencil.h"
#include "spritelayer.h"
#include "player.h"
#include "physics.h"
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

    cConfig* oConfig;
    cPencil* oPencil;
    cSpriteLayer* oLevelLayer;
    cSpriteLayer* oSpritePicker;
    cSprite* oBackgroundLayer;
    cPlayer* oPlayerObject;
    cCamera* oCam;
    cPhysics* oPhysics;

    SDL_Surface *sScreenSurface;
    SDL_Surface *sTextSurface;

    list<iLevelObject*> lLevelObjects;

    cWorld();
    ~cWorld();




protected:
private:
};

#endif // WORLD_H
