#ifndef WORLD_H
#define WORLD_H

#include <list>
#include "config.h"
#include "pencil.h"
#include "spritelayer.h"
#include "player.h"
#include "camera.h"
#include "ilevelobject.h"
#include "levelobject.h"

using namespace std;

class cWorld
{
    public:
        cConfig* oConfig;
        cPencil* oPencil;
        cSpriteLayer* oLevelLayer;
        cSpriteLayer* oSpritePicker;
        cSprite* oBackgroundLayer;
        cPlayer* oPlayerObject;
        cCamera* oCam;

        SDL_Surface *sScreenSurface;
        SDL_Surface *sTextSurface;

        list<iLevelObject*> lLevelObjects;

        cWorld();
        ~cWorld();
    protected:
    private:
};

#endif // WORLD_H
