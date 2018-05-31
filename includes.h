#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include <cmath> //This cannot end well

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define R_WIDTH 960
#define R_HEIGHT 720

extern bool debug;
extern bool verbose;
extern bool nointro;
extern bool freeplay;
extern bool fpsdisplay;

extern bool gameover;

extern int screenheight;
extern int screenwidth;

extern Mix_Chunk* quarterup;
extern Mix_Chunk* jingle;
extern Mix_Chunk* lazer;
extern Mix_Chunk* boom;

enum TEAM { PLAYER, ENEMIES, NONE};
enum ACTOR_STATE { ALIVE, DESTROYED, RESPAWNING, INVINCIBLE };
enum ACTOR_DIRECTION { RIGHT, LEFT, UP, DOWN };

enum SHOT_TYPE { DEFAULT, RAPID, CHARGE, BOMB, MINE };

enum BOSS_STATE { NEUTRAL, EXITING };

enum ENGINE_STATE { INTRO, TITLE, DEMO, PREMISSION, MISSION, NAMEENTRY };

//Why the hell were those in Entities.h ?! Was I drunk ?
SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string texturename);
SDL_Texture* LoadInterfaceElement(SDL_Renderer* renderer, std::string texturename);
SDL_Texture* LoadBG(SDL_Renderer* renderer, std::string levelfolder, std::string texturename);
SDL_Texture* TextureFromText(SDL_Renderer* renderer, std::string text, int fontsize = 0);
SDL_Texture* TextureFromTextShaded(SDL_Renderer* renderer, std::string text, unsigned int w_width = 0, int fontsize = 0);

//Texture wrapper classes. Trust me it's going to simplify a lot of stuff down the line
class Gfx
{
public:
    SDL_Texture* texture;
    SDL_Rect rect;
    unsigned short alpha;

    Gfx(SDL_Renderer* renderer, std::string name, unsigned short nalpha = 255);
    Gfx();
    ~Gfx();
    void AutoSize();
    void SetAlpha(unsigned short nalpha);
    void AutoAlpha();
    void Render(SDL_Renderer* renderer);
};

class Sprite : public Gfx
{
public:
    Sprite(SDL_Renderer* renderer, std::string name, unsigned short nalpha = 255);
    Sprite();
    ~Sprite();
};

class Background : public Gfx
{
public:
    Background(SDL_Renderer* renderer, int levelid, std::string name, unsigned short nscrollspeed = 5, unsigned short nalpha = 255);
    Background();
    ~Background();
    void Scroll(SDL_Renderer* renderer);

    unsigned short scrollspeed;
};

class UIElement : public Gfx
{
public:
    UIElement(SDL_Renderer* renderer, std::string name, unsigned short nalpha = 255);
    UIElement();
    ~UIElement();
};

class Text : public Gfx
{
public:
    Text(SDL_Renderer* renderer, std::string text, unsigned short nalpha = 255, int fontsize = 0);
    Text();
    ~Text();
};

class ShadedText : public Gfx
{
public:
    ShadedText(SDL_Renderer* renderer, std::string text, unsigned short nalpha = 255, int fontsize = 0);
    ShadedText();
    ~ShadedText();
};

//Define custom exceptions here
class PlayerCharacterDeleted : public std::exception
{
public:
    const char * what () const throw ()
    {
    	return "PlayerCharacterDeletedException";
    }
};

class EmptyActorList : public std::exception
{
public:
    const char * what () const throw ()
    {
    	return "EmptyActorListException";
    }
};

class NotImplementedException : public std::exception
{
public:
    const char * what () const throw ()
    {
    	return "FIXME: Feature not implemented !!";
    }
};

#endif // _INCLUDES_H
