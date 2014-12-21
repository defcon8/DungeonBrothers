#include "..\include\config.h"

cConfig::cConfig()
{
    //Todo: get these from a config file.
    screenwidth=640;
    screenheight=480;
    screenbits=16;
    virtualresolution=false;
    debughost = "127.0.0.1";
    debugport = 55555;
    //Do not tune this
    SDLflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
}

cConfig::~cConfig() {}
