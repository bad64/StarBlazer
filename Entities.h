#include "includes.h"

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string texturename);

class Actor
{
public:
    ACTOR_TYPE type;
    std::string name;

    SDL_Texture* spritesheet;
    SDL_Rect currentsprite;

    int xspeed;
    int yspeed;
    SDL_Rect renderquad;

    int lifetime;

    //Generic flags
    ACTOR_STATE state;
    ACTOR_DIRECTION direction;

    //Constructor/Destructor
    Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny);
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
    void Behave(int playerx, int playery, int frames);
    PlayerClass(SDL_Renderer* renderer, std::string nname, int nx, int ny);
    ~PlayerClass();
};

class EnemyClass : public Actor
{
public:
    ENEMY_SUBTYPE subtype;

    EnemyClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, ENEMY_SUBTYPE nsubtype);;
    ~EnemyClass();
};

class BossClass : public Actor
{
public:
    BOSS_STATE boss_ai_state;
    BossClass(SDL_Renderer* renderer, std::string nname, int nx, int ny);
    ~BossClass();
};
