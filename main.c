/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with DevC++ on Win32.
  2013
  
  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
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
