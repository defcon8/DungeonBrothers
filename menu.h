/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

#ifndef MENU_H
#define MENU_H

#include "menuitem.h"
#include <vector>

using namespace std;

class cMenu
{
    public:
        cMenu();
        virtual ~cMenu();
        vector<cMenuItem> menuitems;
        vector<cMenuItem> menupath;
    protected:
    private:
        void buildMenu();


};

#endif // MENU_H
