#ifndef _ENTITIES_H
#define _ENTITIES_H

#include "../../includes.h"

class Actor
{
public:
    Actor(SDL_Renderer* renderer, std::string nname, int nframe, int nxpos, int nypos, int nxspeed, int nyspeed, int nHP = 1, int nTTL = -1, int nshotcd = 30);
    ~Actor();

    Actor* parent;
    Sprite* sprite;
    int HP;
    int frame;

    TEAM team;

    int startxpos, startypos;

    int pattern;
    int pattern_state;

    SDL_Rect cliprect;

    int xspeed, yspeed;
    int createdOnFrame, timeToLive, animationFrame;
    int invincibilityStart, invincibilityDuration;
    int lastShot, shotCooldownTimer, maxShots, activeShots;

    int shot_xspeed, shot_yspeed;

    bool controlsLocked;    //Only useful for the player
    bool stop;
    bool shotsLocked;
    bool isInvincible;      //Invincibility stops bullets
    bool isTransparent;     //"Transparent" means it ignores bullets
    bool doDraw;            //Basically, we don't draw what does not need to be drawn (aka whatever is off-screen)
    bool markForDelete;

    SDL_Rect hbox;  //Hit box
    SDL_Point center;

    int hbox_x_offset, hbox_y_offset;

    virtual void Update();
    virtual void Shoot(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
    virtual void Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);

    void SetInvincible(int onFrame, int nduration = 60);
    void SetTimeToLive(int TTL);
};

//Derived classes are really just alternate constructors in a more convenient form

class Player : public Actor
{
public:
    Player(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord, int shotcd);
    ~Player();

    void Update();
    void Shoot(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
    void Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
};

class Bullet : public Actor
{
public:
    Bullet(SDL_Renderer* renderer, int currentframe, Actor* nparent, int xcoord, int ycoord, int nxspeed, int nyspeed);
    ~Bullet();

    void Update();
    void Shoot(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
    void Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
};
class EnemyBullet : public Bullet
{
public:
    EnemyBullet(SDL_Renderer* renderer, int currentframe, Actor* nparent, int xcoord, int ycoord, int nxspeed, int nyspeed);
    ~EnemyBullet();
};

class Meteor : public Actor
{
public:
    Meteor(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord);
    ~Meteor();

    void Update();
};

class Regular : public Actor
{
public:
    Regular(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord, int npattern, int shotcd);
    ~Regular();

    void Update();
    //void Shoot(SDL_Renderer* renderer, int currentframe, Actor*& target, std::vector<Actor*> *Actors);
    void Shoot(SDL_Renderer* renderer, int currentframe, int targetx, int targety, std::vector<Actor*> *Actors);
    void Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
};

#endif // _ENTITIES_H
