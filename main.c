#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define DEBUG 1

int main (int argc, char *argv[])
{
    cGame* oGame = new cGame;
    
    oGame->Start();
    
    delete oGame;
    
    return 0;
}
