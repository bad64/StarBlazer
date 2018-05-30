#include "Entities.h"

Explosion::Explosion(SDL_Renderer* renderer, int currentframe, int xcoord, int ycoord) : Actor(renderer, "splosion", currentframe, xcoord, ycoord, 0, 0, 1, 60, 999)
{
    doNotReplace = true;
    ignoreCollisions = true;

    std::cout << "BOOM ! " << doNotReplace << std::endl;
}
Explosion::~Explosion()
{

}

void Explosion::Update()
{
    animationFrame++;

    if (animationFrame % 5 == 0)
    {
        if (frame + 1 < 6)
            frame++;
        else
            frame = 0;
    }

    cliprect.x = frame*50;
}

void Explosion::Behave(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{
    if (currentframe == createdOnFrame + timeToLive)
        markForDelete = true;
}
