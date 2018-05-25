#include "LevelTemplate.h"

Level1::Level1(int nid) : Level(nid)
{

}
Level1::~Level1()
{

}

void Level1::ReadScript(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors)
{
    if (currentframe == 0)
    {
        Actors->clear();
    }
    else if (currentframe == 1)
    {
        Actors->emplace(Actors->begin(), new Player(renderer, currentframe, 100, screenheight/2, 30));
    }
    else if (currentframe == 300)
    {
        /*Actors->emplace_back(new Meteor(renderer, currentframe, 900, -100));
        Actors->emplace_back(new Meteor(renderer, currentframe, 800, -400));
        Actors->emplace_back(new Meteor(renderer, currentframe, 700, -700));
        Actors->emplace_back(new Meteor(renderer, currentframe, 600, -1000));
        Actors->emplace_back(new Meteor(renderer, currentframe, 500, -1300));*/
    }
    else if (currentframe == 60)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*2/10, 1, 110));
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*8/10, 1, 110));
    }
    else if (currentframe == 520)
    {
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*2/10, 1, 90));
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*8/10, 1, 90));
    }
    else if (currentframe == 540)
    {
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*2/10, 1, 70));
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*8/10, 1, 70));
    }
    else if (currentframe == 560)
    {
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*2/10, 1, 50));
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*8/10, 1, 50));
    }
    else if (currentframe == 580)
    {
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*2/10, 1, 30));
        //Actors->emplace_back(new Regular(renderer, currentframe, screenwidth + 100, screenheight*8/10, 1, 90));
    }
}
