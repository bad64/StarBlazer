#include "Engine.h"

void NoNameEngine::CollisionDetection()
{
    for (unsigned int i = 0; i < mission->Actors.size(); i++)
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
                                        std::cout << "Player ate a meteor or something" << std::endl;
                                        lives--;
                                    }

                                    if (!mission->Actors.at(i)->isInvincible)
                                    {
                                        mission->Actors.at(i)->HP--;
                                    }

                                }
                            }
                            else if (mission->Actors.at(j)->isTransparent == true) //Ship colliding with a bullet
                            {
                                if (SDL_HasIntersection(&mission->Actors.at(i)->hbox, &mission->Actors.at(j)->hbox))
                                {
                                    if (i == 0)
                                    {
                                        std::cout << "Player got shot the f down" << std::endl;
                                        lives--;
                                    }
                                    else
                                    {
                                        std::cout << "Enemy got shot the f down at " << mission->Actors.at(i)->sprite->rect.x << ":" << mission->Actors.at(i)->sprite->rect.y << std::endl;
                                        score += 100;
                                    }

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
}
