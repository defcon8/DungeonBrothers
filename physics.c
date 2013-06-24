#include "physics.h"

cPhysics::cPhysics(cConfig* oConfigRef)
{
    //ctor
    iGravity=oConfigRef->iPhysicsGravity;
}

cPhysics::~cPhysics()
{
    //dtor
}
