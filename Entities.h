#include "includes.h"

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

    //Method to define behavior of a bit of everything, really
    void Behave(int playerx, int playery, int frame);
    void Shoot();
};

class Player : public Actor
{
public:
    int lives;
    int score;
    int bombs;
    bool controls;
    void Respawn();
    void Behave(int playerx, int playery, int frame);
    Player(SDL_Renderer* renderer, std::string nname, int nx, int ny);
    ~Player();
};

class Enemy : public Actor
{
public:
    ENEMY_SUBTYPE subtype;

    Enemy(SDL_Renderer* renderer, std::string nname, int nx, int ny, ENEMY_SUBTYPE nsubtype);;
    ~Enemy();
    void Behave(int playerx, int playery, int frame);
};

class Boss : public Actor
{
public:
    BOSS_STATE boss_ai_state;
    Boss(SDL_Renderer* renderer, std::string nname, int nx, int ny);
    ~Boss();
    void Behave(int playerx, int playery, int frame);
};
