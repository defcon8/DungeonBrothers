#include "world.h"

cWorld::cWorld()
{
    config = new cConfig();
    menu = new cMenu();
    pencil = new cPencil();
    cam = new cCamera(this);
    physics = new cPhysics(config);
}

cWorld::~cWorld()
{
}
