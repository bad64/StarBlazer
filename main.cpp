#include "Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    /* Parsing command line arguments */
    bool debug = false;

    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--debug")
        {
            cout << "Debug mode enabled" << endl;
            debug = true;
        }
    }
    /* End command line arguments */

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
    uint64_t currentframe = 0;
    Timer timer = Timer();
    //END Frame counter subsystem

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    Game.ActorsList.emplace_back(Player(renderer, "Player", 50, 300, 0, NULL));
    //Game.ActorsList[0].shottype = RAPID;

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

                if (event.key.keysym.sym == SDLK_a)
                {
                    switch (Game.ActorsList[0].shottype)
                    {
                    case DEFAULT:
                        cout << "Switched shot type to RAPID" << endl;
                        Game.ActorsList[0].shottype = RAPID;
                        break;
                    case RAPID:
                        cout << "Switched shot type to DEFAULT" << endl;
                        Game.ActorsList[0].shottype = DEFAULT;
                        break;
                    case CHARGE:
                        break;
                    case BOMB:
                        break;
                    case MINE:
                        break;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        //This is the part where you need to refer to the various Engine headers to figure out what's going on

        //Test area
        if (Game.ActorsList.size() < 2)
        {
            Game.ActorsList.emplace_back(Enemy(renderer, "Testificate", WIDTH + 100, HEIGHT/2, currentframe, BOMBER, NULL));
        }
        //End of test area

        Game.UpdateDisplay(renderer, keyboard, currentframe);
        if (debug)  //Displays hitbox overlay
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
            for (unsigned int i = 0; i < Game.ActorsList.size(); i++)
            {
                SDL_RenderFillRect(renderer, &Game.ActorsList[i].hitbox);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        if (Game.ActorsList.size() > 1) //No point looking for collisions if the only thing on the screen is the player
            Game.CollisionDetection();

        Game.GarbageCollector();

        SDL_RenderPresent(renderer);
        ++currentframe;

        if (timer.GetSeconds() != seconds)
        {
            if (debug)
                cout << "Frames per second: " << currentframe / timer.GetSeconds() << endl;
            seconds = timer.GetSeconds();
        }
    }

    return 0;
}
