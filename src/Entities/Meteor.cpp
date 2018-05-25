#include "Entities.h"

Meteor::Meteor(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord) : Actor(renderer, "meteor", currentframe, xcoord, ycoord, -1, 7, 1, -1, -1)
{
    isInvincible = true;
    team = ENEMIES;

    if (debug)
        std::cout << "Created a meteor" << std::endl;
}
Meteor::~Meteor()
{
    if (debug)
        std::cout << "Deleted a meteor" << std::endl;
}

void Meteor::Update()
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
        else if (sprite->rect.x < -sprite->rect.w)
        {
            markForDelete = true;
        }
    }

    if (sprite->rect.y >= screenheight + sprite->rect.h)
    {
        sprite->rect.y = startypos;
    }

    if (sprite->rect.x <= -sprite->rect.w)
    {
        if (debug)
            std::cout << "Marked a meteor for deletion" << std::endl;
        markForDelete = true;
    }
}

//void Meteor::Behave()
