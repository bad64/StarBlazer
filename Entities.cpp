#include "Entities.h"

using namespace std;

//This needs to be defined before the engine itself, even though it is basically an engine method
SDL_Texture* LoadTexture(SDL_Renderer* renderer, string texturename)
{
    //Short explanation: With the previous inline loading method, we could not automatically free the memory previously allocated to
    //the SDL_Surface we need to load as a base to convert into a VRAM-usable texture (SDL_Surfaces can't be stored in the VRAM).
    //It may or may not end up saturating the memory on some weaker systems if the game is left to run for extended periods of time,
    //but I'd rather fix that problem preemptively.
    //It was also much harder to handle errors, so all in all, this is a noticeable improvement

    SDL_Surface* t_surface = IMG_Load( string( string("resources/gfx/") + string(texturename) + string(".png") ).c_str() );

    if (!t_surface)
    {
        cout << "FIXME: Could not load resources/gfx/" << texturename << ".png, defaulting to fallback texture" << endl;
        t_surface = IMG_Load( string("resources/gfx/error.png").c_str() );
    }

    SDL_Texture* t_texture = SDL_CreateTextureFromSurface(renderer, t_surface);
    SDL_FreeSurface(t_surface);
    return t_texture;
}

Actor::Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent)
{
    type = GENERIC;
    subtype = NONE;
    state = ALIVE;

    name = nname;
    hitpoints = 1;  //Unless specific cases, that should always be 1
    parent = nparent;
    createdOnFrame = currentframe;
    timeToLive = -1; //Unless it's a bullet, it should be -1
    lockedOnFrame = 0;
    lockout = 0;
    xspeed = 0;
    yspeed = 0;

    spritesheet = LoadTexture(renderer, name);
    currentsprite.x = 0;
    currentsprite.y = 0;
    currentsprite.w = 50;
    currentsprite.h = 50;

    renderquad.x = nx;
    renderquad.y = ny;
    renderquad.w = 50;
    renderquad.h = 50;

    hitbox.x = renderquad.x + renderquad.w/2 - 10;
    hitbox.y = renderquad.y + renderquad.h/2 - 10;
    hitbox.w = 25;
    hitbox.h = 25;

    bone_gun.w = 0;
    bone_gun.h = 0;

    /*cout << nname << " created with state " << state << endl;
    if (parent != NULL)
    {
        cout << "Parent is " << parent->name << endl;
    }
    else
    {
        cout << "No parent" << endl;
    }*/
}
Actor::~Actor()
{
    //cout << "Destroyed " << name << endl;
}

Player::Player(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent) : Actor(renderer, nname, nx, ny, currentframe, nparent)
{
    type = PLAYER;
    subtype = NONE;
    shottype = DEFAULT;

}
Player::~Player()
{

}

Enemy::Enemy(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, ACTOR_SUBTYPE nsubtype, Actor* nparent) : Actor(renderer, nname, nx, ny, currentframe, nparent)
{
    type = ENEMY;
    subtype = nsubtype;

    bone_gun.x = 0;
    bone_gun.y = 25;
    bone_gun.w = 0;
    bone_gun.h = 0;

    hitbox.x = renderquad.x;
    hitbox.y = renderquad.y;
    hitbox.w = renderquad.w;
    hitbox.h = renderquad.h;

    switch (subtype)
    {
    case NONE:
        break;
    case REGULAR:
        xspeed = -5;
        yspeed = 0;
        break;
    case BOMBER:
        xspeed = -5;
        yspeed = 0;
        break;
    case KAMIKAZE:
        xspeed = -10;
        yspeed = 0;
        break;
    case TANK:
        xspeed = -5;
        yspeed = 0;
        break;
    }
}
Enemy::~Enemy()
{

}

Bullet::Bullet(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent) : Actor(renderer, nname, nx, ny, currentframe, nparent)
{
    type = BULLET;
    subtype = NONE;
    shottype = DEFAULT;

    switch (parent->shottype)
    {
    case DEFAULT:
        if (parent->type == ENEMY)
        {
            currentsprite.x = 8;
            currentsprite.y = 5;
            currentsprite.w = 16;
            currentsprite.h = 5;
            timeToLive = -1;
        }
        else
        {
            currentsprite.x = 8;
            currentsprite.y = 0;
            currentsprite.w = 16;
            currentsprite.h = 5;
            timeToLive = -1;
        }

        renderquad.w = 16;
        renderquad.h = 5;
        parent->lockout = 45;
        xspeed = 15;
        yspeed = parent->yspeed;
        break;
    case RAPID:
        currentsprite.x = 0;
        currentsprite.y = 0;
        currentsprite.w = 8;
        currentsprite.h = 8;
        timeToLive = 10;
        renderquad.w = 8;
        renderquad.h = 8;
        parent->lockout = 5;
        xspeed = 20;
        break;
    case CHARGE:
        break;
    case BOMB:
        break;
    case MINE:
        break;
    }

    hitbox.x = renderquad.x;
    hitbox.y = renderquad.y;
    hitbox.w = renderquad.w;
    hitbox.h = renderquad.h;
}
Bullet::~Bullet()
{

}
