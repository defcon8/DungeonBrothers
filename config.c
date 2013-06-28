#include "config.h"

cConfig::cConfig()
{
    //ctor
    //Todo: get these from config file.
    m_iScreenWidth=1024;
    m_iScreenHeight=768;
    m_iScreenBits=16;

    //Do not tune this
    iSDLFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
}

cConfig::~cConfig()
{
    //dtor
}
