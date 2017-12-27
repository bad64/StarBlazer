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
    Engine Game = Engine();

    //Frame counter subsystem
    uint32_t seconds = 0;
    uint64_t frames = 0;
    Timer timer = Timer();
    //END Frame counter subsystem

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    PlayerClass test = PlayerClass(renderer, "Player", 0, 0);

    Game.ActorsList.push_back(move(test));

    while(loop)
    {
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
                if (event.key.keysym.sym == SDLK_g)
                {
                    Game.ActorsList[0].state = DESTROYED;
                }
            }

        }

        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        //This is the part where you need to refer to the various Engine headers to figure out what's going on

        //Test area
        /*for (int i = 0; i < Game.ActorsList.size(); i++)
            Game.TheAlmightyController(&Game.ActorsList[i]);*/

        Game.UpdateDisplay(renderer);
        Game.GarbageCollector();
        //End of test area

        SDL_RenderPresent(renderer);
        ++frames;

        if (timer.GetSeconds() != seconds)
        {
            //cout << "Frames per second: " << frames / timer.GetSeconds() << endl;
            seconds = timer.GetSeconds();
        }
    }

    return 0;
}
