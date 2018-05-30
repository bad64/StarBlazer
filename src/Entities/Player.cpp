#include "Entities.h"

Player::Player(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord, int shotcd) : Actor(renderer, "player", currentframe, xcoord, ycoord, 0, 0, 1, -1, 10)
{
    pattern = 0;
    doDraw = true;
    team = PLAYER;
    hbox_x_offset = hbox_y_offset = 15;
    hbox.w = hbox.h = 20;
    xspeed = yspeed = 0;
    isInvincible = false;

    maxShots = 3;

    if (debug)
        std::cout << "Created the player at " << this << " with parent " << parent << std::endl;
}
Player::~Player()
{
    if (debug)
        std::cout << "Destroyed the player (if that happens while a mission is running, you screwed up)" << std::endl;
}

void Player::Update()
{
    cliprect.x = 0;
    doDraw = true;

    sprite->rect.x += xspeed;
    sprite->rect.y += yspeed;

    hbox.x = sprite->rect.x + hbox_x_offset;
    hbox.y = sprite->rect.y + hbox_y_offset;

    center.x = sprite->rect.x + sprite->rect.w/2;
    center.y = sprite->rect.y + sprite->rect.h/2;
}

void Player::Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{
    //Shot limiter
    if ((shotsLocked == true) && (currentframe == shotCooldownTimer + lastShot))
    {
        shotsLocked = false;
        activeShots = 0;
        shotCooldownTimer = 10;
    }

    //Respawn
    if (controlsLocked)
    {
        if (currentframe == invincibilityStart + 60)
        {
            controlsLocked = false;
        }
        else
        {
            xspeed = 5;
        }
    }
    if (currentframe == invincibilityStart + invincibilityDuration)
    {
        isInvincible = false;
    }

    //Invincibility flicker
    if (isInvincible)
    {
        if (currentframe % 2 == 0)
            doDraw = false;
        else
            doDraw = true;
    }
}

void Player::Shoot(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{
    if (!stop)
    {
        int ydelta;
        if (yspeed < 0)
            ydelta = yspeed * -1/2;
        else if (yspeed >= 0)
            ydelta = yspeed/2;

        Actors->emplace_back(new Bullet(renderer, currentframe, this, center.x, center.y, 10-ydelta, yspeed/2));
        lastShot = currentframe;
        activeShots+=1;

        if (activeShots == 3)
        {
            shotsLocked = true;
            shotCooldownTimer = 60;
        }
    }
    else
    {
        Actors->emplace_back(new Bullet(renderer, currentframe, this, center.x, center.y, shot_xspeed, shot_yspeed));
        lastShot = currentframe;
        activeShots+=1;
    }

    std::cout << activeShots << " shots active" << std::endl;
}
