#include "config.h"

cConfig::cConfig()
{
    //ctor
    //Todo: get these from config file.
    m_iScreenWidth=640;
    m_iScreenHeight=480;
    m_iScreenBits=16;

    iPhysicsGravity=1;

    //Do not tune this
    iSDLFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;

}

cConfig::~cConfig()
{
    //dtor
}
