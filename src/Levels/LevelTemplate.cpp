#include "LevelTemplate.h"

int Level::g_levelid = 0;

Level::Level(int nid)
{
    levelid = nid;
}
Level::Level()
{
    Level::g_levelid++;
    levelid = Level::g_levelid;
    bgm = NULL;
}
Level::~Level()
{

}

void Level::ReadScript(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{

}

void Level::Load(SDL_Renderer* renderer)
{
    try
    {
        layer4[0] = new Background(renderer, levelid, "layer4", 1, 255);
        layer4[0]->rect.x = 0;
        layer4[0]->rect.y = 0;

        layer4[1] = new Background(renderer, levelid, "layer4", 1, 255);
        layer4[1]->rect.x = layer4[0]->rect.w;
        layer4[1]->rect.y = 0;
    }
    catch (...)
    {
        std::cout << "Level has no layer 4 (that's bad)" << std::endl;
    }

    try
    {
        layer3[0] = new Background(renderer, levelid, "layer3", 2, 255);
        layer3[0]->rect.x = 0;
        layer3[0]->rect.y = 0;

        layer3[1] = new Background(renderer, levelid, "layer3", 2, 255);
        layer3[1]->rect.x = layer3[0]->rect.w;
        layer3[1]->rect.y = 0;
    }
    catch (...)
    {
        std::cout << "Level has no layer 3 (is this intended ?)" << std::endl;
    }
}
void Level::Unload()
{
    for (int i = 0; i < 2; i++)
    {
        SDL_DestroyTexture(layer4[i]->texture);
        SDL_DestroyTexture(layer3[i]->texture);
    }
    Mix_HaltMusic();
    Mix_FreeMusic(bgm);
}
