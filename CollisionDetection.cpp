#include "Engine.h"

using namespace std;

//Take a wild guess at what this does.

void Engine::CollisionDetection()
{
    for (unsigned int i = 1; i < ActorsList.size(); i++)
    {
        if (ActorsList[i].parent != NULL)
        {
            if (ActorsList[i].type == BULLET)
            {
                for (unsigned int j = 0; j < ActorsList.size(); j++)
                {
                    if ((ActorsList[j].type == ActorsList[i].parent->type) || (ActorsList[j].type == ActorsList[i].type))
                        continue;
                    else
                    {
                        if (SDL_HasIntersection(&ActorsList[i].hitbox, &ActorsList[j].hitbox))
                        {
                            cout << ActorsList[j].name << " shot down by " << ActorsList[i].parent->name << endl;
                            Trash(i);
                            Trash(j);
                        }
                    }
                }
            }
        }
        else if (ActorsList[i].parent == NULL)  //That pretty much has to be an enemy ship
        {
            if (SDL_HasIntersection(&ActorsList[0].renderquad, &ActorsList[i].renderquad) == SDL_TRUE)
            {
                cout << "Player rammed by " << ActorsList[i].name << endl;
            }
        }
    }
}
