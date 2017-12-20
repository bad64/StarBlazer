#include "Entities.h"

using namespace std;

Actor::Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny)
{
    name = nname;

    try
    {
        renderquad.x = nx;
        renderquad.y = ny;
        renderquad.w = 75;
        renderquad.h = 75;
    }
    catch (...)
    {
        cout << "Something went terribly wrong in the definition of the render quad" << endl;
        //If you see this, triple check your instance declaration. You likely called the constructor wrong

        renderquad.x = 0;
        renderquad.y = 0;
        renderquad.w = 75;
        renderquad.h = 75;
    }

    try
    {
        spritesheet = SDL_CreateTextureFromSurface(renderer, IMG_Load( string( string("resources/gfx/") + string(name) + string(".png") ).c_str() ));
        cout << "Loaded spritesheet for " << name << endl;
    }
    catch (...)
    {
        cout << "Can't locate the spritesheet for " << name << endl;
        //If you see this, the program will crash. No exceptions. Check path, etc
        //TODO: Fallback spritesheet to prevent said crash
    }

    currentsprite.x = 0;
    currentsprite.y = 0;
    currentsprite.w = 75;
    currentsprite.h = 75;

    state = ALIVE;
}
Actor::~Actor()
{

}

Player::Player(SDL_Renderer* renderer, std::string nname, int nx, int ny) : Actor(renderer, nname, nx, ny)
{
    lives = 3;
    score = 0;
    bombs = 20;
    controls = false;
    type = PLAYER;
    direction = RIGHT;
    xspeed = 0;
    yspeed = 0;
}
Player::~Player()
{

}

void Player::Behave(int playerx, int playery, int frame)
{
    renderquad.x += xspeed;
    renderquad.y += yspeed;

    switch (direction)
    {
    case RIGHT:
        currentsprite.x = 0;
        currentsprite.y = 0;
        break;
    case LEFT:
        currentsprite.x = 75;
        currentsprite.y = 0;
        break;
    case UP:
        currentsprite.x = 150;
        currentsprite.y = 0;
        break;
    case DOWN:
        currentsprite.x = 225;
        currentsprite.y = 0;
        break;
    }
}

void Player::Respawn()
{
    state = INVINCIBLE;
}

Enemy::Enemy(SDL_Renderer* renderer, std::string nname, int nx, int ny, ENEMY_SUBTYPE nsubtype) : Actor(renderer, nname, nx, ny)
{
    type = ENEMY;
    subtype = nsubtype;
    direction = LEFT;

    switch (nsubtype)
    {
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
    }
}

void Enemy::Behave(int playerx, int playery, int frame)
{
    switch (this->subtype)
    {
    case REGULAR:
        break;
    case BOMBER:
        this->renderquad.x += this->xspeed;

        if ((this->renderquad.x < (WIDTH * 6) / 10))
        {
            if (this->xspeed != 5)
                this->xspeed += 1;
        }
        else if (this->renderquad.x > WIDTH - 150)
        {
            if (this->xspeed != -5)
                this->xspeed -= 1;
        }
        break;
    case KAMIKAZE:
        break;
    }
}
