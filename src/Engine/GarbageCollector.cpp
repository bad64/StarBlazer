#include "Engine.h"

void NoNameEngine::GarbageCollector()
{
    for (unsigned int i = 0; i < mission->Actors.size(); i++)
    {
        if ((mission->Actors[i]->HP <= 0) || (currentframe == mission->Actors[i]->createdOnFrame + mission->Actors[i]->timeToLive))
        {
            mission->Actors[i]->markForDelete = true;
        }
    }

    for (unsigned int j = 0; j < mission->Actors.size(); j++)
    {
        if (mission->Actors[j]->markForDelete)
        {
            if (mission->Actors[j]->isTransparent)
            {
                mission->Actors[j]->parent->activeShots--;  //This causes a data race. SOLVE ASAP
            }

            mission->Actors.erase(mission->Actors.begin()+j);
            j--;
        }
    }
}
