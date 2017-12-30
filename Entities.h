#include "includes.h"

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string texturename);

class Actor
{
public:
    //Flags to determine what the hell are we looking at
    ACTOR_TYPE type;
    ACTOR_SUBTYPE subtype;
    SHOT_TYPE shottype;
    ACTOR_STATE state;
    ACTOR_DIRECTION direction;

    //Generic attributes
    std::string name;
    int hitpoints;
    Actor* parent; //Useful for collision detection
    int createdOnFrame;
    int timeToLive;
    int lockedOnFrame;
    int lockout;
    int xspeed, yspeed;

    //Sprite data
    SDL_Texture* spritesheet;
    SDL_Rect currentsprite;

    //Hitbox data
    SDL_Rect renderquad; //Where we render the actor
    SDL_Rect hitbox;
    SDL_Rect bone_gun;

    Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent);
    ~Actor();
};

class Player : public Actor
{
public:
    Player(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent);
    ~Player();
};

class Enemy : public Actor
{
public:
    Enemy(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, ACTOR_SUBTYPE nsubtype, Actor* nparent);
    ~Enemy();
};

class Bullet : public Actor
{
public:
    Bullet(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent);
    ~Bullet();
};
