#ifndef CONFIG_H
#define CONFIG_H

#include <SDL/SDL.h>

class cConfig {
public:
    int screenwidth, screenheight, screenbits;
    Uint32 SDLflags;
    SDL_Surface* screen;
    cConfig();
    ~cConfig();
protected:
private:
};

#endif // CONFIG_H
