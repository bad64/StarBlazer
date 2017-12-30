#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define WIDTH 1280
#define HEIGHT 720

enum ACTOR_TYPE { PLAYER, ENEMY, BULLET, FRIENDLY, BOSS };
enum ACTOR_SUBTYPE { NONE, REGULAR, BOMBER, KAMIKAZE, TANK };
enum ACTOR_STATE { ALIVE, DESTROYED, INVINCIBLE };
enum ACTOR_DIRECTION { RIGHT, LEFT, UP, DOWN };

enum SHOT_TYPE { DEFAULT, RAPID, CHARGE, BOMB, MINE };

enum BOSS_STATE { NEUTRAL, EXITING };
