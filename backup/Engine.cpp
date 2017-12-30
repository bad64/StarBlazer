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

void Engine::Shoot(SDL_Renderer* renderer, Actor* who, int currentframe)
{
    ActorsList.emplace_back(Bullet(renderer, who, currentframe));
}

void Engine::UpdateDisplay(SDL_Renderer* renderer, const uint8_t* keyboard, int currentframe)
{
    for (unsigned int i = 0; i < ActorsList.size(); i++)
    {
        if (ActorsList[i].state != DESTROYED)
        {
            if (i == 0)
                TheAlmightyController(&ActorsList[i], keyboard, currentframe);
            else
            {
                if (ActorsList[i].type == ENEMY)
                    TheAlmightyController(&ActorsList[0], &ActorsList[i], currentframe);
                else if (ActorsList[i].type == BULLET)
                    TheAlmightyController(&ActorsList[i], currentframe);
            }

            SDL_RenderCopy(renderer, ActorsList[i].spritesheet, &ActorsList[i].currentsprite, &ActorsList[i].renderquad);
        }
        else
        {
            Trash(i);
        }
    }
}

void Engine::Trash(int index)
{
    Garbage.push_back(move(ActorsList[index]));
    ActorsList.erase(ActorsList.begin() + index);
}

void Engine::GarbageCollector()
{
    if (!Garbage.empty())
    {
        //cout << "Garbage size: " << Garbage.size() << endl;
        Garbage.erase(Garbage.begin(), Garbage.end());
    }
    //else
        //cout << "Garbage is empty" << endl;
}
