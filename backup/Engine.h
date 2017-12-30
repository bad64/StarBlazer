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

    void Spawn(SDL_Renderer* renderer, Actor* parent, int currentframe);
    void Shoot(SDL_Renderer* renderer, Actor* who, int currentframe);

    void CollisionDetection();

    void UpdateDisplay(SDL_Renderer* renderer, const uint8_t* keyboard, int currentframe);

    void TheAlmightyController(Actor* player, const uint8_t* keyboard, int currentframe);
    void TheAlmightyController(Actor* player, Actor* enemy, int currentframe);
    void TheAlmightyController(Actor* bullet, int currentframe);

    void Trash(int index);
    void GarbageCollector();
};
