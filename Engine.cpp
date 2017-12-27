#include "Engine.h"


//Timer section
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

//Engine section
Engine::Engine()
{

}
Engine::~Engine()
{

}

void Engine::GarbageCollector()
{
    if (!Garbage.empty())
    {
        Garbage.erase(Garbage.begin(), Garbage.end());
    }
}

void Engine::UpdateDisplay(SDL_Renderer* renderer)
{
    for (unsigned int i = 0; i < ActorsList.size(); i++)
    {
        if (ActorsList[i].state != DESTROYED)
        {
            this->TheAlmightyController(&ActorsList[i]);
            SDL_RenderCopy(renderer, ActorsList[i].spritesheet, &ActorsList[i].currentsprite, &ActorsList[i].renderquad);
        }
        else
        {
            Garbage.push_back(move(ActorsList[i]));
        }
    }
}
