#include "Entities.h"

Bullet::Bullet(SDL_Renderer* renderer, int currentframe, Actor* nparent, int xcoord, int ycoord, int nxspeed, int nyspeed) : Actor (renderer, "bullet", currentframe, xcoord, ycoord, nxspeed, nyspeed, 1, 180)
{
    isTransparent = true;
    doNotReplace = true;
    parent = nparent;
    team = nparent->team;

    sprite->rect.w = sprite->rect.h = 15;
    cliprect.w = cliprect.h = 15;
    hbox.w = hbox.h = 15;

    if (debug)
    {
        std::cout << "Created a bullet with parent " << parent << std::endl;
        std::cout << "Created on frame " << createdOnFrame << " with " << timeToLive << " frames to live" << std::endl;
    }
}
Bullet::~Bullet()
{
    if (debug)
        std::cout << "Destroyed a bullet" << std::endl;
}

EnemyBullet::EnemyBullet(SDL_Renderer* renderer, int currentframe, Actor* nparent, int xcoord, int ycoord, int nxspeed, int nyspeed) : Bullet(renderer, currentframe, nparent, xcoord, ycoord, nxspeed, nyspeed)
{
    isTransparent = true;
    doNotReplace = true;
    parent = nparent;
    team = nparent->team;

    sprite->texture = LoadTexture(renderer, "enemybullet");

    sprite->rect.w = sprite->rect.h = 15;
    cliprect.w = cliprect.h = 15;
    hbox.w = hbox.h = 15;

    if (debug)
    {
        std::cout << "Created a bullet with parent " << parent << std::endl;
        std::cout << "Created on frame " << createdOnFrame << " with " << timeToLive << " frames to live" << std::endl;
    }
}
EnemyBullet::~EnemyBullet()
{
    if (debug)
        std::cout << "Destroyed a bullet" << std::endl;
}

void Bullet::Update()
{
    if (frame + 1 < 6)
        frame++;
    else
        frame = 0;

    cliprect.x = frame*15;

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
            std::cout << "No longer drawing bullet" << std::endl;
        }
        else if ((sprite->rect.x < -sprite->rect.w) || (sprite->rect.y > screenheight + sprite->rect.h) || (sprite->rect.x > screenwidth + sprite->rect.w) || (sprite->rect.y < -sprite->rect.h))
        {
            if (debug)
                std::cout << "Marked a bullet for deletion" << std::endl;
            markForDelete = true;
        }
    }
}

void Bullet::Shoot(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{

}

void Bullet::Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{

}
