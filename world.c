#include "world.h"

cWorld::cWorld() {
    //ctor
    oConfig = new cConfig();
    oPencil = new cPencil();
    oCam = new cCamera(this);
    oPhysics = new cPhysics(oConfig);
}

cWorld::~cWorld() {
    //dtor
}
