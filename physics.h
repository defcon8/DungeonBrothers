#ifndef PHYSICS_H
#define PHYSICS_H

#include "config.h"

class cPhysics
{
    public:
        int iGravity;

        cPhysics(cConfig* oConfigRef);
        ~cPhysics();
    protected:
    private:
};

#endif // PHYSICS_H
