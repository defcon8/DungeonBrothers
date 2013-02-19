#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define DEBUG 1

/*
 PLEASE NOTE: the program will require SDL.dll which is located in
              dev-c++'s dll directory. You have to copy it to you
			  program's home directory or the path.
 */

int main (int argc, char *argv[])
{
    cGame* oGame = new cGame;
    
    oGame->Start();
    
    delete oGame;
    
    return 0;
}
