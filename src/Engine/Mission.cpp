#include "Engine.h"

Mission::Mission(SDL_Renderer* renderer)
{
    currentlevel = nullptr;
}
Mission::Mission()
{
    currentlevel = nullptr;
}
Mission::~Mission()
{

}

void Mission::Load(SDL_Renderer* renderer, int levelindex)
{
    Actors.clear();
    switch (levelindex)
    {
    case 1:
        currentlevel = new Level1(1);
        break;
    /*case 2:
        currentlevel = new Level2(2);
        break;
    case 3:
        currentlevel = new Level3(3);
        break;
    case 4:
        currentlevel = new Level4(4);
        break;*/
    default:
        currentlevel = new Level(0);
        break;
    }
    currentlevel->Load(renderer);
}
void Mission::Unload()
{
    currentlevel->Unload();
    Actors.clear();
}

void NoNameEngine::MissionLoop()
{
    SDL_SetRenderTarget(renderer, scene);

    for (unsigned int i = 0; i < mission->Actors.size(); i++)
    {
        mission->Actors[i]->Update();
        mission->Actors[i]->Behave(renderer, currentframe, &mission->Actors);
    }

    mission->currentlevel->ReadScript(renderer, currentframe, &mission->Actors);

    CollisionDetection();

    Render();
    GarbageCollector();
}

