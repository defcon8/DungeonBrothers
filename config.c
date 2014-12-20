#include "config.h"

cConfig::cConfig()
{
    //Todo: get these from a config file.
    screenwidth=1024;
    screenheight=768;
    screenbits=16;
    virtualresolution=true;

    //Do not tune this
    SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
}

cConfig::~cConfig() {}
