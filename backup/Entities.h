#include "includes.h"

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string texturename);

class Actor
{
public:
    ACTOR_TYPE type;
    ACTOR_SUBTYPE subtype;
    std::string name;
    Actor* parent;

    SDL_Texture* spritesheet;
    SDL_Rect currentsprite;

    SDL_Rect bone_gun;

    int xspeed;
    int yspeed;
    SDL_Rect renderquad;

    int createdOnFrame;
    int timeToLive;

    //Generic flags
    ACTOR_STATE state;
    ACTOR_DIRECTION direction;
    SHOT_TYPE shottype;

    //Constructor/Destructor
    Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent);
    ~Actor();

    void Info();
};

class PlayerClass : public Actor
{
public:
    int lives;
    int score;
    int bombs;
    bool controls;

    void Respawn();

    PlayerClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent);
    ~PlayerClass();
};

class EnemyClass : public Actor
{
public:
    EnemyClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, ACTOR_SUBTYPE nsubtype, int currentframe, Actor* nparent);;
    ~EnemyClass();
};

class BossClass : public Actor
{
public:
    BOSS_STATE boss_ai_state;
    BossClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent);
    ~BossClass();
};

class Bullet : public Actor
{
public:
    Actor* parent;

    Bullet(SDL_Renderer* renderer, Actor* nparent, int currentframe);
    ~Bullet();
};
