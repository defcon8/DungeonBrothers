/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

#include "..\include\menu.h"

cMenu::cMenu()
{
    buildMenu();
}

void cMenu::buildMenu()
{

    cMenuItem item1,
              item2,
              item3,
              item3s1,
              item3s2,
              item3s3,
              item4;

    item1.name = "Start Game";
    item1.actionid = 0;

    item2.name = "Editor";
    item2.actionid = 100;

    item3.name = "Options";
    item3.actionid = 200;

    item3s1.name = "Return to Main Menu";
    item3.menuitems.push_back(item3s1);
    item3s2.name = "Audio";
    item3s2.actionid = 202;
    item3.menuitems.push_back(item3s2);
    item3s3.name = "Video";
    item3s3.actionid = 203;
    item3.menuitems.push_back(item3s3);
    item4.name = "Exit";
    item4.actionid = 300;


    menuitems.push_back(item1);
    menuitems.push_back(item2);
    menuitems.push_back(item3);
    menuitems.push_back(item4);

}

cMenu::~cMenu()
{
    //dtor
}
