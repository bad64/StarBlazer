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

Actor::Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent = NULL)
{
    name = nname;
    createdOnFrame = currentframe;
    parent = nparent;

    try
    {
        renderquad.x = nx;
        renderquad.y = ny;
        renderquad.w = 50;
        renderquad.h = 50;
    }
    catch (...)
    {
        cout << "Something went terribly wrong in the definition of the render quad" << endl;
        //If you see this, triple check your instance declaration. You likely called the constructor wrong

        renderquad.x = 0;
        renderquad.y = 0;
        renderquad.w = 50;
        renderquad.h = 50;
    }

    spritesheet = LoadTexture(renderer, name);

    currentsprite.x = 0;
    currentsprite.y = 0;
    currentsprite.w = 50;
    currentsprite.h = 50;

    state = ALIVE;

    cout << nname << " created with state " << state << endl;
    if (parent != NULL)
    {
        cout << "Parent is " << parent->name << endl;
    }
    else
    {
        cout << "No parent" << endl;
    }
}
Actor::~Actor()
{
    cout << "Destroyed " << name << endl;
}

void Actor::Info()
{
    cout << name << " at " << renderquad.x << ":" << renderquad.y << endl;
    cout << "Type is ";
    switch (type)
    {
    case PLAYER:
        cout << "PLAYER";
        break;
    case ENEMY:
        cout << "ENEMY";
        break;
    case BULLET:
        cout << "BULLET";
        break;
    case FRIENDLY:
        cout << "FRIENDLY";
        break;
    case BOSS:
        cout << "BOSS";
        break;
    }

    cout << " and state is ";

    switch (state)
    {
    case ALIVE:
        cout << "ALIVE";
        break;
    case DESTROYED:
        cout << "DESTROYED";
        break;
    case INVINCIBLE:
        cout << "INVINCIBLE";
        break;
    }

    cout << endl;

    cout << "xspeed: " << xspeed << endl;
    cout << "yspeed: " << yspeed << endl;

}

PlayerClass::PlayerClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent = NULL) : Actor(renderer, nname, nx, ny, currentframe, nparent)
{
    lives = 3;
    score = 0;
    bombs = 20;
    controls = false;

    type = PLAYER;
    direction = RIGHT;
    shottype = DEFAULT;

    bone_gun.x = renderquad.x + 45;
    bone_gun.y = renderquad.y + 45;
    bone_gun.w = 0;
    bone_gun.h = 0;

    xspeed = 0;
    yspeed = 0;
}
PlayerClass::~PlayerClass()
{

}

void PlayerClass::Respawn()
{
    state = INVINCIBLE;
}

EnemyClass::EnemyClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, ACTOR_SUBTYPE nsubtype, int currentframe, Actor* nparent = NULL) : Actor(renderer, nname, nx, ny, currentframe, nparent)
{
    type = ENEMY;
    subtype = nsubtype;
    direction = LEFT;

    bone_gun.x = 0;
    bone_gun.y = 25;
    bone_gun.w = 0;
    bone_gun.h = 0;

    timeToLive = -1;

    switch (nsubtype)
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
EnemyClass::~EnemyClass()
{

}

BossClass::BossClass(SDL_Renderer* renderer, std::string nname, int nx, int ny, int currentframe, Actor* nparent = NULL) : Actor(renderer, nname, nx, ny, currentframe, nparent)
{

}
BossClass::~BossClass()
{

}

Bullet::Bullet(SDL_Renderer* renderer, Actor* nparent, int currentframe) : Actor(renderer, "shots", nparent->bone_gun.x, nparent->bone_gun.y, currentframe, nparent)
{
    name = "shots";
    type = BULLET;
    createdOnFrame = currentframe;
    xspeed = 10;
    yspeed = 0;

    switch (nparent->shottype)
    {
    case DEFAULT:
        if (nparent->type == ENEMY)
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
        break;
    case RAPID:
        currentsprite.x = 0;
        currentsprite.y = 0;
        currentsprite.w = 8;
        currentsprite.h = 8;
        timeToLive = 30;
        break;
    case CHARGE:
        break;
    case BOMB:
        break;
    case MINE:
        break;
    }

    renderquad.w = currentsprite.w;
    renderquad.h = currentsprite.h;
}
Bullet::~Bullet()
{

}
