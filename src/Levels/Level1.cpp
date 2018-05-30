#include "LevelTemplate.h"

Level1::Level1(int nid) : Level(nid)
{
    bgm = Mix_LoadMUS("resources/snd/level1.wav");
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
        Actors->emplace(Actors->begin(), new Player(renderer, currentframe, 100, R_HEIGHT/2, 30));
    }
    else if (currentframe == 200)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 110));
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 1, 110));
    }
    else if (currentframe == 300)
    {
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 1, 50));
    }
    else if (currentframe == 500)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 2, 50));
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 1, 70));
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 1, 70));
    }
    else if (currentframe == 800)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
    }
    else if (currentframe == 900)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
    }
    else if (currentframe == 1000)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 50));
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 1, 50));
        //Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 1, 50));
    }
    else if (currentframe == 1300)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 1, 50));
    }else if (currentframe == 1600)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*7/10, 2, 50));
        Actors->emplace_back(new Meteor(renderer, currentframe, 900, -100));

        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 1, 50));
    }else if (currentframe == 1650)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 2, 50));

    }else if (currentframe == 1800)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 1, 50));
        Actors->emplace_back(new Meteor(renderer, currentframe, 900, -100));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 2, 50));
    }
    else if (currentframe == 1950)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 2150)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 2, 50));
    }
    else if (currentframe == 2350)//7200
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 3, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*7/10, 3, 50));
    }
    else if (currentframe == 2500)
    {
        Actors->emplace_back(new Meteor(renderer, currentframe, 900, -100));

        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 1, 50));
    }
    else if (currentframe == 2650)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 2750)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 50));
    }

    else if (currentframe == 2850)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 1, 50));
    }
    else if (currentframe == 2900)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 50));
    }
    else if (currentframe == 2950)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
    }
    else if (currentframe == 3000)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 1, 50));
    }

    else if (currentframe == 3050)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 3150)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
    }
    else if (currentframe == 3200)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 1, 50));
    }

    else if (currentframe == 2850)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 1, 50));
    }
    else if (currentframe == 2900)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 50));
    }
    else if (currentframe == 2950)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
    }
    else if (currentframe == 3000)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 1, 50));
    }

    else if (currentframe == 3050)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 3150)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
    }
    else if (currentframe == 3200)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 1, 50));
    }

    else if (currentframe == 3300)
    {
        Actors->emplace_back(new Meteor(renderer, currentframe, 900, -100));

        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 1, 50));
    }
    else if (currentframe == 3400)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 3500)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 50));
    }

    else if (currentframe == 3590)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*1/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 3670)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 0, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 1, 50));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 50));
    }
    else if (currentframe == 3700)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 0, 50));
    }
    else if (currentframe == 3730)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 0, 50));
    }
    else if (currentframe == 3770)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*7/10, 0, 50));
    }
    else if (currentframe == 3800)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 0, 50));
    }


    else if (currentframe == 3830)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*9/10, 0, 50));
    }
    else if (currentframe == 3870)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*7/10, 0, 50));
    }
    else if (currentframe == 3900)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*5/10, 0, 50));
    }
    else if (currentframe == 3940)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*3/10, 0, 50));
    }

     else if (currentframe == 4000)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 0, 30));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 0, 30));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 1, 30));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 30));
    }
    else if (currentframe == 4100)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 0, 30));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 0, 30));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 1, 30));
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 30));
    }
    else if (currentframe == 4130)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*8/10, 2, 50));
    }
    else if (currentframe == 4150)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*6/10, 2, 50));
    }
    else if (currentframe == 4180)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*4/10, 2, 50));
    }
    else if (currentframe == 4210)
    {
        Actors->emplace_back(new Regular(renderer, currentframe, R_WIDTH + 100, R_HEIGHT*2/10, 2, 50));
    }
    else if (currentframe == 4500)
    {
        gameover = true;
    }

}
