/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2014

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "game.h"

#define DEBUG 1

int main (int argc, char *argv[])
{
    // Get out of static context.
    cGame* game = new cGame();
    game->start();
    delete game;
    return 0;
}
