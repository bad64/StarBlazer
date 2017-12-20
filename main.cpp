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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    Player test = Player(renderer, "player", 0, 0);

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
                if (event.key.keysym.sym == SDLK_z)
                {
                    test.yspeed = -5;
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    test.yspeed = 5;
                }
                if (event.key.keysym.sym == SDLK_q)
                {
                    test.xspeed = -5;
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    test.xspeed = 5;
                }
            }
            if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_z)
                {
                    test.yspeed = 0;
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    test.yspeed = 0;
                }
                if (event.key.keysym.sym == SDLK_q)
                {
                    test.xspeed = 0;
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    test.xspeed = 0;
                }
            }

        }

        SDL_RenderClear(renderer);
        SDL_RenderFillRect(renderer, NULL);

        //This is the part where you need to refer to the various Engine headers to figure out what's going on
        test.Behave(0, 0, 0);
        SDL_RenderCopy(renderer, test.spritesheet, &test.currentsprite, &test.renderquad);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
