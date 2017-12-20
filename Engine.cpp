#include "Engine.h"

void Engine::UpdateDisplay(SDL_Renderer* renderer)
{
    for (unsigned int i = 0; i < ActorsList.size(); i++)
    {
        if (ActorsList[i].state != DESTROYED)
        {
            //ActorsList[i].Behave(ActorsList[0].xpos, ActorsList[0].ypos, currentframe);
        }
    }
}
