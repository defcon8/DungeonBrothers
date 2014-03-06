#include "config.h"

cConfig::cConfig() {
    //ctor
    //Todo: get these from config file.
    m_iScreenWidth=640;
    m_iScreenHeight=480;
    m_iScreenBits=16;

    //Do not tune this
    iSDLFlags = SDL_HWSURFACE | SDL_DOUBLEBUF;
}

cConfig::~cConfig() {
    //dtor
}
