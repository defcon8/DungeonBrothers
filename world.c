#include "world.h"

cWorld::cWorld() {
    //ctor
    config = new cConfig();
    pencil = new cPencil();
    cam = new cCamera(this);
    physics = new cPhysics(config);
}

cWorld::~cWorld() {
    //dtor
}
