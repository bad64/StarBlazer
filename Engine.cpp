#include "Engine.h"

Timer::Timer()
{
    startedOnTick = SDL_GetTicks();
}
Timer::~Timer()
{

}

void Timer::zero()
{
    startedOnTick = SDL_GetTicks();
}

uint32_t Timer::GetSeconds()
{
    return (SDL_GetTicks() - startedOnTick) / 1000;
}

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
