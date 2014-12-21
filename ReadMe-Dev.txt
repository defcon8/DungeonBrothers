

Hi :),


This is a short document to get you (as developer) up and running.

Dungeon Brothers is written in unmanaged C++ using Codeblocks (13.12) on Windows.
To compile the sources you'll need to obtain following free libraries:

- SDL
- SDL_mixer
_ SDL_ttf

from https://www.libsdl.org/

All the sources for the game and dungeontrace are inside the \src folder.

The Dungeon Brothers codeblocks project file is named DungeonBrothers.cpb.
In this project all the build options are set. I'll strongly advise you to
keep the directory structure and build options intact as they are where when you got the
project from Github. When it won't compile fix the problem and don't mess up
the directory structure or build options. The build options all use relative paths.


Note!!
======
Dungeon Brothers is currently linked to the latest version of SDL v1.2. not v2. So
make sure you have the right versions of SDL and the addon libraries. 
I'm working hard on full SDL v2 support.


Howto use DungeonTrace
======================

DungeonTrace is an small application written in VB.NET. Yes i know VB.NET is ugly, but i wrote
this little trace application a long time ago. Since it works like a charm i don't has any priority. But
it has to be rewritten someday :)

When DungeonTrace.exe is launched it will open a listener socket on port 55555. Therefore always start
DungeonTrace first, and then Dungeon Brothers. 

When Dungeon Brothers (client) is launched, it will initiate a socket connection to localhost:55555. At
this moment the hostname and port are hardcoded. But when changed and recompiled it works over a network
also.

If you are using DungeonTrace for the first time, make sure you enable the desired "traceitems",
which can be selected from the menu "Settings" inside DungeonTrace. The list with traceitems are filled
as soon as the client connects. So understand that the list is empty as long as dungeon brothers is not
connected to the socket.

Traceitems can be switched on and off on the fly during program execution. Your selection of enabled
traceitems is saved in the Windows registry.

Note that enabling many traceitems could slow down dungeon brothers. So i advise you to only
enable items you need.



Final note
======================

It is opensource and feel free to use it any way you like.
If you should make some thing cool with this source or have some contributions, give me a shout :-)

Contact me at:

Bastiaan de Waard
info@bastiaandewaard.com
