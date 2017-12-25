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

Actor::Actor(SDL_Renderer* renderer, std::string nname, int nx, int ny)
{
    name = nname;

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
        currentsprite.x = 50;
        currentsprite.y = 0;
        break;
    case UP:
        currentsprite.x = 100;
        currentsprite.y = 0;
        break;
    case DOWN:
        currentsprite.x = 150;
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
    case TANK:
        xspeed = -5;
        yspeed = 0;
        break;
    }
}
Enemy::~Enemy()
{

}

void Enemy::Behave(int playerx, int playery, int frames)
{
    switch (this->subtype)
    {
    case REGULAR:
        break;
    case BOMBER:
        this->renderquad.x += this->xspeed;
        this->renderquad.y += this->yspeed;

        if (frames % 3 == 0)
        {
            if ((this->renderquad.x < (WIDTH * 4) / 10))
            {
                if (this->xspeed != 5)
                    this->xspeed += 1;
            }
            else if (this->renderquad.x > WIDTH - 150)
            {
                if (this->xspeed != -5)
                    this->xspeed -= 1;
            }

            if ((this->renderquad.y > playery) && (this->yspeed > -8))
            {
                this->yspeed -= 1;
            }
            else if ((this->renderquad.y < playery) && (this->yspeed < 8))
            {
                this->yspeed += 1;
            }

            if (this->renderquad.y < 0)
            {
                this->renderquad.y = 0;
                this->yspeed = 0;
            }
        }
        break;
    case KAMIKAZE:
        break;
    case TANK:
        break;
    }
}
