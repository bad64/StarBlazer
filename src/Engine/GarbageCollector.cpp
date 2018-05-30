#include "Engine.h"

void NoNameEngine::GarbageCollector(int currentframe)
{
    for (unsigned int i = 0; i < mission->Actors.size(); i++)
    {
        if ((mission->Actors[i]->HP <= 0) || (currentframe == mission->Actors[i]->createdOnFrame + mission->Actors[i]->timeToLive))
        {
            if (i == 0)
            {
                if ((lives > 0) && (!mission->Actors[i]->isInvincible))
                {
                    std::cout << lives << " lives remaining" << std::endl;
                    mission->Actors[i]->HP = 1;
                    mission->Actors[i]->isInvincible = true;
                    mission->Actors[i]->controlsLocked = true;
                    mission->Actors[i]->invincibilityStart = currentframe;
                    mission->Actors[i]->invincibilityDuration = 180;
                    mission->Actors[i]->xspeed = 5;
                    mission->Actors[i]->yspeed = 0;

                    mission->Actors[i]->sprite->rect.x = -100;
                    mission->Actors[i]->sprite->rect.y = screenheight/2;
                }
                else if (lives == 0)
                {
                    mission->Actors[i]->sprite->rect.x = -1000;
                    gameover = true;
                    break;
                }
            }
            else
                mission->Actors[i]->markForDelete = true;
        }
    }

    if (!gameover)
    {
        for (unsigned int j = 0; j < mission->Actors.size(); j++)
        {
            if (mission->Actors[j]->markForDelete)
            {
                if ((mission->Actors[j]->isTransparent) && (mission->Actors[j]->parent == mission->Actors[0])) //Catch the bullet
                {
                    std::cout << "Decreasing shot counter to " << mission->Actors[j]->parent->activeShots - 1 << std::endl;

                    if (mission->Actors[j]->parent->activeShots - 1 >= 0)
                        mission->Actors[j]->parent->activeShots--;
                }

                mission->Actors.erase(mission->Actors.begin()+j);
                j--;
            }
        }
    }
}
