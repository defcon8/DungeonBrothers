#ifndef CONFIG_H
#define CONFIG_H

#include <SDL/SDL.h>

class cConfig
{
    public:
        int m_iScreenWidth, m_iScreenHeight, m_iScreenBits;
        SDL_Surface* m_sScreen;
        cConfig();
        ~cConfig();
    protected:
    private:
};

#endif // CONFIG_H
