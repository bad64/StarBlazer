#include "Entities.h"

Regular::Regular(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord, int npattern, int shotcd) : Actor(renderer, "regular", currentframe, xcoord, ycoord, -5, 0, 1, -1, shotcd)
{
    pattern = npattern;
    team = ENEMIES;
}
Regular::~Regular()
{

}

void Regular::Update()
{
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
            if (debug)
                std::cout << "Marked a regular enemy for deletion" << std::endl;
            markForDelete = true;
        }
    }
}

//void Regular::Shoot(SDL_Renderer* renderer, int currentframe, Actor*& target, std::vector<Actor*> *Actors)
void Regular::Shoot(SDL_Renderer* renderer, int currentframe, int targetx, int targety, std::vector<Actor*> *Actors)
{
    lastShot = currentframe;

    if (pattern == 0)
    {
        //Actors->emplace_back(new Bullet(renderer, currentframe, sprite->rect.x, sprite->rect.y+25, -6, 0));
        //shotCooldownTimer = 60;
    }
    else if (pattern == 1)
    {
        SDL_Point self_center = {center.x, center.y};
        SDL_Point target_center = {targetx, targety};
        SDL_Point projection_center = {self_center.x, target_center.y};

        //A is the enemy, B is the player, C is the projection of the player's y coordinate on the enemy's x axis value

        double ab = sqrt(pow(self_center.x - target_center.x, 2) + pow (self_center.y - target_center.y, 2));
        double ac = sqrt(pow(self_center.x - projection_center.x, 2) + pow (self_center.y - projection_center.y, 2));

        double angleBetween = acos(ac/ab) * 180/3.14159265;

        int bulletxvelocity = 0;
        int bulletyvelocity = 0;

        //Surely there is a better way to write this
        //NOTE: All of this was basically written with the "If I put this value here, what does it do ?" method. Do not attempt to reproduce these results while sober.
        if (target_center.y < self_center.y) //If target is above shooter
        {
            if (target_center.x < self_center.x) //If target is on the left
            {
                if ((angleBetween >= 0) && (angleBetween < 11.25))
                {
                    bulletxvelocity = 0;
                    bulletyvelocity = -8;
                }
                else if ((angleBetween >= 11.25) && (angleBetween < 33.75))
                {
                    bulletxvelocity = -2;
                    bulletyvelocity = -6;
                }
                else if ((angleBetween >= 33.75) && (angleBetween < 56.25))
                {
                    bulletxvelocity = -4;
                    bulletyvelocity = -4;
                }
                else if ((angleBetween >= 56.25) && (angleBetween < 78.75))
                {
                    bulletxvelocity = -6;
                    bulletyvelocity = -2;
                }
                else if ((angleBetween >= 78.75) && (angleBetween < 90))
                {
                    bulletxvelocity = -8;
                    bulletyvelocity = 0;
                }
            }
            else if (target_center.x > self_center.x) //If target is on the right
            {
                if ((angleBetween >= 0) && (angleBetween < 11.25))
                {
                    bulletxvelocity = 0;
                    bulletyvelocity = -8;
                }
                else if ((angleBetween >= 11.25) && (angleBetween < 33.75))
                {
                    bulletxvelocity = 2;
                    bulletyvelocity = -6;
                }
                else if ((angleBetween >= 33.75) && (angleBetween < 56.25))
                {
                    bulletxvelocity = 4;
                    bulletyvelocity = -4;
                }
                else if ((angleBetween >= 56.25) && (angleBetween < 78.75))
                {
                    bulletxvelocity = 6;
                    bulletyvelocity = -2;
                }
                else if ((angleBetween >= 78.75) && (angleBetween < 90))
                {
                    bulletxvelocity = 8;
                    bulletyvelocity = 0;
                }
            }
        }
        else if (target_center.y > self_center.y) //If target is below shooter
        {
            if (target_center.x < self_center.x) //If target is on the left
            {
                if ((angleBetween >= 0) && (angleBetween < 11.25))
                {
                    bulletxvelocity = 0;
                    bulletyvelocity = 8;
                }
                else if ((angleBetween >= 11.25) && (angleBetween < 33.75))
                {
                    bulletxvelocity = -2;
                    bulletyvelocity = 6;
                }
                else if ((angleBetween >= 33.75) && (angleBetween < 56.25))
                {
                    bulletxvelocity = -4;
                    bulletyvelocity = 4;
                }
                else if ((angleBetween >= 56.25) && (angleBetween < 78.75))
                {
                    bulletxvelocity = -6;
                    bulletyvelocity = 2;
                }
                else if ((angleBetween >= 78.75) && (angleBetween < 90))
                {
                    bulletxvelocity = -8;
                    bulletyvelocity = 0;
                }
            }
            else if (target_center.x > self_center.x) //If target is on the right
            {
                if ((angleBetween >= 0) && (angleBetween < 11.25))
                {
                    bulletxvelocity = 0;
                    bulletyvelocity = 8;
                }
                else if ((angleBetween >= 11.25) && (angleBetween < 33.75))
                {
                    bulletxvelocity = 2;
                    bulletyvelocity = 6;
                }
                else if ((angleBetween >= 33.75) && (angleBetween < 56.25))
                {
                    bulletxvelocity = 4;
                    bulletyvelocity = 4;
                }
                else if ((angleBetween >= 56.25) && (angleBetween < 78.75))
                {
                    bulletxvelocity = 6;
                    bulletyvelocity = 2;
                }
                else if ((angleBetween >= 78.75) && (angleBetween < 90))
                {
                    bulletxvelocity = 8;
                    bulletyvelocity = 0;
                }
            }
        }

        Actors->emplace_back(new Bullet(renderer, currentframe, this, sprite->rect.x, sprite->rect.y+25, bulletxvelocity, bulletyvelocity));
        shotCooldownTimer = 300;
    }
}

void Regular::Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{
    if (pattern == 0) //tout droit
    {

    }
    else if (pattern == 1) //de haut en bas
    {
        if (sprite->rect.y > screenheight*8/10)
        {
            if (pattern_state != 1)
            {
                pattern_state = 1;
            }
        }
        else if (sprite->rect.y < screenheight*2/10)
        {
            if (pattern_state != 0)
            {
                pattern_state = 0;
            }
        }

        if (pattern_state == 0)
        {
            if ((yspeed < 6) && (currentframe % 2 == 0))
                yspeed+=1;
        }
        else if (pattern_state == 1)
        {
            if ((yspeed > -6) && (currentframe % 2 == 0))
                yspeed-=1;
        }
    }else if (pattern == 2) // rapide puis vas tout droit a la fin
    {
        if (sprite->rect.y > screenheight*7/10)
        {
            if (pattern_state != 1)
            {
                pattern_state = 1;
            }
        }
        else if (sprite->rect.y < screenheight*3/10)
        {
            if (pattern_state != 0)
            {
                pattern_state = 0;
            }
        }
        if (sprite->rect.x < screenwidth*4/10)
        {
            if (pattern_state != 2)
            {
                pattern_state = 2;
            }
        }

        if (pattern_state == 0)
        {
            if ((yspeed < 12) && (currentframe % 2 == 0)) //tant quau dessus monte a chaque frame plus vite
                yspeed+=3;
        }
        else if (pattern_state == 1)
        {
            if ((yspeed > -12) && (currentframe % 2 == 0))
                yspeed-=3;
        }
        else if (pattern_state == 2)
        {
            yspeed = 0;
            if ((xspeed > -10) && (currentframe % 2 == 0))
                xspeed-=2;
        }
    }else if (pattern == 3) //tout droit puis normal mais fixe needed
    {
        if (sprite->rect.x > screenwidth*6/10)
        {
            if (pattern_state != 2 )
            {
                pattern_state = 2;
            }
        }
        else {
            if (pattern_state != 3 && yspeed < 8){
                pattern_state = 3;
            }
            if (sprite->rect.y > screenheight*7/10)
            {
                if (pattern_state != 1)
                {
                    pattern_state = 1;
                }
            }
            else if (sprite->rect.y < screenheight*3/10)
            {
                if (pattern_state != 0)
                {
                    pattern_state = 0;
                }
            }
        }



        if (pattern_state == 0)
        {
            if ((yspeed < 8) && (currentframe % 2 == 0)) //tant quau dessus monte a chaque frame plus vite
                yspeed+=3;
        }
        else if (pattern_state == 1)
        {
            if ((yspeed > -8) && (currentframe % 2 == 0))
                yspeed-=3;
        }
        else if (pattern_state == 2)
        {
            yspeed = 0;
            if ((xspeed > -8) && (currentframe % 2 == 0))
                xspeed-=3;
        }else if (pattern_state == 3){
            if ((yspeed < 10) && (currentframe % 2 == 0))
                yspeed+=3;
        }
    }

    //patern utilisant start pos pour changer patern

    if (currentframe == lastShot + shotCooldownTimer)
        Shoot(renderer, currentframe, Actors->at(0)->center.x, Actors->at(0)->center.y, Actors);
}
