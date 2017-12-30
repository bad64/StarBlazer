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

    void Shoot(SDL_Renderer* renderer, Actor* who, int currentframe);

    //Essentials
    void CollisionDetection();
    void UpdateDisplay(SDL_Renderer* renderer, const uint8_t* keyboard, int currentframe);

    //Controller functions
    void MovementController(SDL_Renderer* renderer, Actor* target, const uint8_t* keyboard, int currentframe);      //Controls the player movement
    void MovementController(Actor* target, Actor* enemy, int currentframe);                 //Controls the enemy movement
    void MovementController(Actor* bullet, int currentframe);                               //Controls bullet movement

    //Garbage collection & deletion
    void Trash(int index);
    void GarbageCollector();
};
