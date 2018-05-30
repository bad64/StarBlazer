#include "Engine.h"

void NoNameEngine::CollisionDetection()
{
    for (unsigned int i = 0; i < mission->Actors.size(); i++)
    {
        if (mission->Actors.at(i)->ignoreCollisions == false)
        {
            if (mission->Actors.at(i)->isTransparent == false) //This should be a ship
            {
                for (unsigned int j = 0; j < mission->Actors.size(); j++)
                {
                    if (i != j)
                    {
                        if (mission->Actors[i]->team != mission->Actors[j]->team)
                        {
                            if ((mission->Actors.at(i) != mission->Actors.at(j)->parent))
                            {
                                if (mission->Actors.at(j)->isTransparent == false) //Ship colliding with a ship
                                {
                                    if (SDL_HasIntersection(&mission->Actors.at(i)->hbox, &mission->Actors.at(j)->hbox) == SDL_TRUE)
                                    {
                                        if (i == 0)
                                        {
                                            if (!mission->Actors.at(0)->isInvincible)
                                                lives--;
                                        }

                                        if (!mission->Actors.at(i)->isInvincible)
                                        {
                                            mission->Actors.at(i)->HP--;
                                        }
                                        Mix_PlayChannel(-1, boom, 0);
                                    }
                                }
                                else if (mission->Actors.at(j)->isTransparent == true) //Ship colliding with a bullet
                                {
                                    if (SDL_HasIntersection(&mission->Actors.at(i)->hbox, &mission->Actors.at(j)->hbox))
                                    {
                                        if (i == 0)
                                        {
                                            if (!mission->Actors.at(0)->isInvincible)
                                                lives--;
                                        }
                                        else
                                        {
                                            score += 100;
                                        }
                                        Mix_PlayChannel(-1, boom, 0);

                                        if (!mission->Actors.at(i)->isInvincible)
                                        {
                                            mission->Actors.at(i)->HP--;
                                        }

                                        mission->Actors.at(j)->HP--;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (mission->Actors.at(i)->isTransparent == false)   //This should be a bullet. If this isn't a bullet, something is terroriffically wrong.
            {
                //Just don't check from the bullet's POV. Doing so increases CPU usage for basically no reason.
                //Let the ships figure out themselves whether or not they have been hit by a bullet.
            }
        }
        else
        {
            std::cout << "Skipping collision check for " << i << std::endl;
        }
    }
}
