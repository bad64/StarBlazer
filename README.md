# StarBlazer
Retro shmup using C++ and SDL2

Depends on:
SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

To compile this project, you need to link in the following order:
-lmingw32 if you are on Windows
-lSDL2main
-lSDL2
-lSDL2_image
-lSDL2_ttf
-lSDL2_mixer

Any C++ compiler supporting C++14 should work, so basic MinGW32 on Windows won't. You will need MinGW-w64 with SJLJ and POSIX threads. Don't forget the -mwindows switch if you're on Windows !
