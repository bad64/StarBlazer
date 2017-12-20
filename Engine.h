#include "Entities.h"

using namespace std;

class Engine
{
public:
    vector<Actor> ActorsList;
    int currentframe;
    void UpdateDisplay(SDL_Renderer* renderer);
};
