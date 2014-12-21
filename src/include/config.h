#ifndef CONFIG_H
#define CONFIG_H

#include <SDL/SDL.h>
#include <string>

using namespace std;

class cConfig {
public:
    int screenwidth;
    int screenheight;
    int screenbits;
    int debugport;
    string debughost;
    bool virtualresolution;
    Uint32 SDLflags;
    SDL_Surface* screen;
    cConfig();
    ~cConfig();
protected:
private:
};

#endif // CONFIG_H
