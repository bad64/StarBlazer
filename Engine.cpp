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
    ActorsList.emplace_back(Bullet(renderer, "shots", who->bone_gun.x, who->bone_gun.y, currentframe, who));
}

void Engine::UpdateDisplay(SDL_Renderer* renderer, const uint8_t* keyboard, int currentframe)
{
    for (unsigned int i = 0; i < ActorsList.size(); i++)
    {
        if (ActorsList[i].state != DESTROYED)
        {
            if (currentframe == ActorsList[i].createdOnFrame + ActorsList[i].timeToLive)
            {
                ActorsList[i].state = DESTROYED;
                continue;
            }
            else
            {
                if (i == 0)     //That's the player
                    MovementController(renderer, &ActorsList[0], keyboard, currentframe);

                switch (ActorsList[i].type)
                {
                case GENERIC:
                    break;
                case PLAYER:
                    break;
                case ENEMY:
                    MovementController(&ActorsList[0], &ActorsList[i], currentframe);
                    break;
                case BULLET:
                    MovementController(&ActorsList[i], currentframe);
                    break;
                case FRIENDLY:
                    break;
                case BOSS:
                    break;
                }
                SDL_RenderCopy(renderer, ActorsList[i].spritesheet, &ActorsList[i].currentsprite, &ActorsList[i].renderquad);
            }
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
        Garbage.erase(Garbage.begin(), Garbage.end());
    }
}
