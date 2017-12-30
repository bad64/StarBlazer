#include "Engine.h"

using namespace std;

//Take a wild guess at what this does.

void Engine::CollisionDetection()
{
    for (unsigned int i = 1; i < ActorsList.size(); i++)
    {
        if (ActorsList[i].parent != NULL)
        {
            if (ActorsList[i].parent->type != PLAYER) //That's an enemy bullet
            {
                if (SDL_HasIntersection(&ActorsList[0].renderquad, &ActorsList[i].renderquad) == SDL_TRUE)
                {
                    cout << "Collision with " << ActorsList[i].name << " fired by " << ActorsList[i].parent->name << endl;
                }
            }
            else if (ActorsList[i].parent->type == PLAYER) //That's fired by the player
            {
                for (unsigned int j = 0; j < ActorsList.size(); j++)
                {
                    if (ActorsList[i].parent == ActorsList[j].parent)
                        continue;
                    else
                    {
                        cout  << ActorsList[j].name << " shot down by " << ActorsList[i].parent->name << endl;
                        ActorsList[i].state = DESTROYED;
                        ActorsList[j].state = DESTROYED;
                    }
                }
            }
            else
                continue;
        }
        else if (ActorsList[i].parent == NULL)   //That'd usually be an enemy
        {
            if (SDL_HasIntersection(&ActorsList[0].renderquad, &ActorsList[i].renderquad) == SDL_TRUE)
            {
                ActorsList[0].renderquad.x = 5;
                ActorsList[0].renderquad.y = 250;
                cout << "Collision with " << ActorsList[i].name << endl;
            }
        }
    }
}
