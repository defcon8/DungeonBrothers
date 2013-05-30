/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

#ifndef LEVELOBJECT_H_
#define LEVELOBJECT_H_

class iLevelObject {
  public:
        virtual ~iLevelObject() {}
        virtual void fUpdate() = 0;
};

#endif /* LEVELOBJECT_H_ */
