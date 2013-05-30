/*

  Dungeon Brothers
  Opensource C++ Platform Game by Bastiaan de Waard (defcon8)
  Makes use of the SDL Library. Compiled with CodeBlocks/MingW on Win32.
  2013

  W.  https://github.com/defcon8/DungeonBrothers
  W.  http://www.bastiaandewaard.com
  E.  info@bastiaandewaard.com

*/

class cCamera {

  private:

  public:

  int up;
  int right;
  int down;
  int left;
  int none;

  cCamera();
  ~cCamera();
  int X,Y;
  int Direction;
};

