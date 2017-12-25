#include "Entities.h"

using namespace std;

class Timer
{
public:
    Timer();
    ~Timer(); //You shouldn't have to call this, ever
    void zero();
    uint32_t GetSeconds();

    uint32_t startedOnTick;
};

class Engine
{
public:
    vector<Actor> ActorsList;
    int currentframe;
    void UpdateDisplay(SDL_Renderer* renderer);
};
