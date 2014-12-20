#include "config.h"

cConfig::cConfig() {
    //Todo: get these from a config file.
    screenwidth=640;
    screenheight=480;
    screenbits=16;

    //Do not tune this
    SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
}

cConfig::~cConfig() {}
