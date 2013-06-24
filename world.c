#include "world.h"

cWorld::cWorld()
{
    //ctor
    oConfig = new cConfig();
    oPencil = new cPencil();
    oCam = new cCamera();
}

cWorld::~cWorld()
{
    //dtor
}
