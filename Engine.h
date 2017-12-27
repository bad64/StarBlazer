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
    Engine();   //Should never have
    ~Engine();  //to call these either

    vector<Actor> ActorsList;
    vector<Actor> Garbage;

    void UpdateDisplay(SDL_Renderer* renderer);

    void TheAlmightyController(Actor* player);
    void TheAlmightyController(Actor* player, Actor* enemy);

    void GarbageCollector();
};
