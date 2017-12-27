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

enum ACTOR_TYPE { PLAYER, ENEMY, FRIENDLY, BOSS };
enum ACTOR_STATE { ALIVE, DESTROYED, INVINCIBLE };
enum ACTOR_DIRECTION { RIGHT, LEFT, UP, DOWN };

enum ENEMY_SUBTYPE { REGULAR, BOMBER, KAMIKAZE, TANK };

enum SHOT_TYPE { DEFAULT, RAPID, CHARGE };

enum BOSS_STATE { NEUTRAL, EXITING };
