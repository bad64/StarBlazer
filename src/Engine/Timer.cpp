#include "Engine.h"

using namespace std;

Timer::Timer()
{
    startedOnTick = SDL_GetTicks();
    seconds = 0;
}
Timer::~Timer()
{

}

void Timer::zero()
{
    startedOnTick = SDL_GetTicks();
    seconds = 0;
}

uint32_t Timer::GetSeconds()
{
    return (SDL_GetTicks() - startedOnTick) / 1000;
}
