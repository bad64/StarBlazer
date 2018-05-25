#include "Entities.h"

Actor::Actor(SDL_Renderer* renderer, std::string nname, int nframe, int nxpos, int nypos, int nxspeed, int nyspeed, int nHP, int nTTL, int nshotcd)
{
    frame = 0;
    pattern_state = 0;

    parent = nullptr;
    sprite = new Sprite(renderer, nname);
    createdOnFrame = nframe;
    animationFrame = createdOnFrame;
    HP = nHP;
    lastShot = createdOnFrame;
    shotCooldownTimer = nshotcd;
    timeToLive = nTTL;

    sprite->rect.x = startxpos = nxpos;
    sprite->rect.y = startypos = nypos;
    sprite->rect.w = sprite->rect.h = 50;

    center.x = sprite->rect.x + sprite->rect.w/2;
    center.y = sprite->rect.y + sprite->rect.h/2;

    hbox_x_offset = hbox_y_offset = 0;

    hbox.w = hbox.h = 50;

    cliprect = {frame*50, 0, 50, 50};

    isInvincible = false;
    doDraw = false;
    controlsLocked = false;
    markForDelete = false;

    xspeed = nxspeed;
    yspeed = nyspeed;
}
Actor::~Actor()
{

}


void Actor::Update()
{
    animationFrame++;

    if (animationFrame % 5 == 0)
    {
        if (frame + 1 < 6)
            frame++;
        else
            frame = 0;
    }

    cliprect.x = frame*50;

    sprite->rect.x += xspeed;
    sprite->rect.y += yspeed;

    hbox.x = sprite->rect.x + hbox_x_offset;
    hbox.y = sprite->rect.y + hbox_y_offset;

    center.x = sprite->rect.x + sprite->rect.w/2;
    center.y = sprite->rect.y + sprite->rect.h/2;

    if ((sprite->rect.x >= -sprite->rect.w) && (sprite->rect.x <= screenwidth) && (sprite->rect.y >= -sprite->rect.h) && (sprite->rect.y <= screenheight))
    {
        if (!doDraw)
        {
            doDraw = true;
        }
    }
    else
    {
        if (doDraw)
        {
            doDraw = false;
        }
        else if ((sprite->rect.x < -sprite->rect.w) || (sprite->rect.y > screenheight + sprite->rect.h))
        {
            markForDelete = true;
        }
    }
}

void Actor::Shoot(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{
    Actors->emplace_back(new Bullet(renderer, currentframe, this, sprite->rect.x, sprite->rect.y+25, 6, 0));
}

void Actor::Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{

}
