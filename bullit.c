// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
// *** END ***
#include "bullit.h"
#include "world.h"
#include <cmath>

cBullit::cBullit(cWorld* _world, const char* tilesource, int spriteheight, int spritewidth, int _angle, int _speed) : cLevelObject(_world, tilesource, spriteheight, spritewidth)
{
    angle = _angle;
    speed = _speed;

    x = _world->playerobject->x;
    y = _world->playerobject->y + (_world->playerobject->gfxlayer->source->spriteheight / 2);

    //Setup Layer
    gfxlayer = new cSpriteLayer(_world,1,1,spriteheight,spritewidth,false,false,true,0,0,0);

    //Setup Source
    gfxlayer->source->spritespacer = 0;
    gfxlayer->source->setColorKey(0,0,0);
    gfxlayer->source->load(tilesource);
    gfxlayer->source->spritewidthoffset = 0;
    gfxlayer->source->spriteheightoffset = 0;
    gfxlayer->source->spriteheight = spriteheight;
    gfxlayer->source->spritewidth = spritewidth;

    //choose player sprite
    gfxlayer->leveldata[0][0].type=SPRITE;
    gfxlayer->leveldata[0][0].row=0;
    gfxlayer->leveldata[0][0].index=0;
}

cBullit::~cBullit()
{}

void cBullit::aI()
{
    //Movement
    velocityx=(cos(angle*(3.14/180))*speed);
    velocityy=(sin(angle*(3.14/180))*speed);

    x+= velocityx;
    y+= velocityy;
    TRACE("Bullit","Object destroyed CamX: %d",world->config->screenwidth-world->cam->x);
    if((x < 0) || (x > (world->config->screenwidth-world->cam->x))) {
        isalive=false;
    }

}
