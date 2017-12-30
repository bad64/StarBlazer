#include "Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Star Blazer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bool loop = true;
    SDL_Event event;
    const uint8_t* keyboard = SDL_GetKeyboardState(NULL);
    bool spacebarlock = false;
    Engine Game = Engine();

    //Frame counter subsystem
    uint32_t seconds = 0;
    uint64_t currentframe = 0;
    Timer timer = Timer();
    //END Frame counter subsystem

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    PlayerClass test = PlayerClass(renderer, "Player", 100, 500, 0, NULL);

    Game.ActorsList.push_back(move(test));

    while(loop)
    {
        SDL_PumpEvents();

        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                loop = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    loop = false;
                }
            }
            if (keyboard[SDL_SCANCODE_SPACE])
            {
                if (!spacebarlock)
                {
                    Game.Shoot(renderer, &Game.ActorsList[0], currentframe);
                    spacebarlock = true;
                }
                else
                    continue;
            }
            else if (!keyboard[SDL_SCANCODE_SPACE])
                spacebarlock = false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        //This is the part where you need to refer to the various Engine headers to figure out what's going on

        //Test area
        Game.UpdateDisplay(renderer, keyboard, currentframe);

        if (Game.ActorsList.size() > 1)
            Game.CollisionDetection();

        if (currentframe % 30 == 0)
            Game.GarbageCollector();
        //End of test area

        SDL_RenderPresent(renderer);
        ++currentframe;

        if (Game.ActorsList.size() < 2)
        {
            Game.ActorsList.emplace_back(EnemyClass(renderer, "Kamikaze", WIDTH + 100, 500, KAMIKAZE, currentframe, NULL));
        }

        if (timer.GetSeconds() != seconds)
        {
            //cout << "Frames per second: " << currentframe / timer.GetSeconds() << endl;
            seconds = timer.GetSeconds();
        }
    }

    return 0;
}
