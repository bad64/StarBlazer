#include "src/Engine/Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    /* Parsing command line arguments */
    bool fullscreen = false;

    /*Frame counter related*/
    unsigned int fps;
    SDL_Texture* tx_fps = NULL;
    SDL_Rect rect_fps = {5,5,0,0};

    for (int i = 0; i < argc; i++)
    {
        if ((argv[i][0] == '-') && (argv[i][1] != '-'))
        {
            for (unsigned int j = 1; j < sizeof(argv[i]); j++)
            {
                if (argv[i][j] == 'd')
                {
                    cout << "Debug mode enabled" << endl;
                    debug = true;
                }
                else if (argv[i][j] == 'v')
                {
                    cout << "Debug mode verbosity increased" << endl;
                    debug = true;
                    verbose = true;
                }
                else if (argv[i][j] == 'w')
                {
                    try
                    {
                        screenwidth = std::atoi(argv[i+1]);
                        cout << "Set width to " << screenwidth << endl;
                    }
                    catch (...)
                    {
                        cout << "Invalid width supplied; defaulting to 960px" << endl;
                    }
                }
                else if (argv[i][j] == 'h')
                {
                    try
                    {
                        screenheight = std::atoi(argv[i+1]);
                        cout << "Set height to " << screenheight << endl;
                    }
                    catch (...)
                    {
                        cout << "Invalid height supplied; defaulting to 720px" << endl;
                    }
                }
            }
        }
        else
        {
            if (string(argv[i]) == "--fps")
            {
                cout << "FPS counter enabled" << endl;
                fpsdisplay = true;
            }
            else if (string(argv[i]) == "--fullscreen")
            {
                fullscreen = true;
            }
            else if (string(argv[i]) == "--freeplay")
            {
                freeplay = true;
            }
            else if (string(argv[i]) == "--nointro")
            {
                nointro = true;
            }
        }
    }

    /* End command line arguments */

    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    //Useful sounds
    Mix_Chunk* quarterup = Mix_LoadWAV("resources/snd/InsertCoin.wav");
    Mix_Chunk* lazer = Mix_LoadWAV("resources/snd/Lazer.wav");

    //Let's do some joystick stuff
    SDL_Joystick* gamepad = NULL;

    if(SDL_NumJoysticks() < 1)
    {
        std::cout << "No joysticks detected" << std::endl;
    }
    else
    {
        std::cout << "Found " << SDL_NumJoysticks() << " joysticks" << std::endl;

        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            std::cout << SDL_JoystickNameForIndex(i) << " ";
            if (SDL_IsGameController(i))
                std::cout << "supported by the GameController API" << std::endl;
            else
                std::cout << "NOT supported by the GameController API" << std::endl;

            std::cout << "      " << SDL_JoystickNumAxes(SDL_JoystickOpen(i)) << " axes" << std::endl;
            std::cout << "      " << SDL_JoystickNumButtons(SDL_JoystickOpen(i)) << " buttons" << std::endl;
            std::cout << "      " << SDL_JoystickNumHats(SDL_JoystickOpen(i)) << " hats" << std::endl;
        }
    }
    gamepad = SDL_JoystickOpen(0);
    bool joystick_start = false;
    bool joystick_select = false;
    SDL_JoystickEventState(SDL_ENABLE);

    SDL_Window* window = NULL;
    if (!fullscreen)
        window = SDL_CreateWindow("Star Blazer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight, SDL_WINDOW_SHOWN);
    else
    {
        window = SDL_CreateWindow("Star Blazer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenwidth, screenheight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
        SDL_ShowCursor(SDL_DISABLE);
    }

    NoNameEngine Engine = NoNameEngine(window, screenwidth, screenheight);  //Learn to love and hate this thing at the same time

    bool loop = true;
    SDL_Event event;
    const uint8_t* keyboard = SDL_GetKeyboardState(NULL);

    SDL_SetRenderDrawBlendMode(Engine.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Engine.renderer, 0, 0, 0, 255);

    while (loop)
    {
        if ((joystick_start) && (joystick_select))
            loop = false;

        SDL_PumpEvents();
        SDL_SetRenderTarget(Engine.renderer, Engine.scene);
        SDL_RenderClear(Engine.renderer);
        SDL_RenderFillRect(Engine.renderer, NULL);

        //Primary input loop
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
                    if ((Engine.credits < 99) && (!freeplay) && ((Engine.state == TITLE) || (Engine.state == DEMO)))
                    {
                        Engine.credits++;
                        Mix_PlayChannel(-1, quarterup, 0);
                        Engine.ModCredits();
                    }
                    else if ((freeplay)  && (Engine.state == DEMO))
                    {
                        Engine.ResetToTitle();
                    }
                }

                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    if (((Engine.credits >= 1) || (freeplay)) && (Engine.state == TITLE))
                    {
                        Engine.FadeOut();
                        Engine.levelready = false;
                    }
                }
                if (event.key.keysym.sym == SDLK_F1)
                {
                    Engine.FullReset();
                }
                if (event.key.keysym.sym == SDLK_F2)
                {
                    Engine.ResetToTitle();
                }
                if (event.key.keysym.sym == SDLK_F3)
                {
                    Engine.flag_goto_title = true;
                }
            }
            if (gamepad != NULL)
            {
                if (event.type == SDL_JOYBUTTONDOWN)
                {
                    if (event.jbutton.button == 6)
                    {
                        joystick_select = true;
                        if ((Engine.credits < 99) && (!freeplay) && ((Engine.state == TITLE) || (Engine.state == DEMO)))
                        {
                            Engine.credits++;
                            Mix_PlayChannel(-1, quarterup, 0);
                            Engine.ModCredits();
                        }
                        else if ((freeplay)  && (Engine.state == DEMO))
                        {
                            Engine.ResetToTitle();
                        }
                    }
                    if (event.jbutton.button == 7)
                    {
                        if (((Engine.credits >= 1) || (freeplay)) && (Engine.state == TITLE))
                        {
                            Engine.FadeOut();
                            Engine.levelready = false;
                        }
                        joystick_start = true;
                    }
                }
                if (event.type == SDL_JOYBUTTONUP)
                {
                    if (event.jbutton.button == 6)
                    {
                        joystick_select = false;
                    }
                    if (event.jbutton.button == 7)
                    {
                        joystick_start = false;
                    }
                }
            }
        }

        if (Engine.GetState() == INTRO)
        {
            if (!nointro)
            {
                try
                {
                    Engine.IntroLoop();
                }
                catch (NotImplementedException& e)
                {
                    //Should no longer be needed
                    Engine.SetState(TITLE);
                }
            }
            else
            {
                try
                {
                    Engine.NoIntroLoop();
                }
                catch (NotImplementedException& e)
                {
                    Engine.SetState(TITLE);
                }
            }

        }
        else if (Engine.GetState() == TITLE)
        {
            try
            {
                Engine.MainMenuLoop();
            }
            catch (NotImplementedException& e)
            {
                //If this happens, someone has likely fucked up
                cout << e.what() << endl;
                Engine.SetState(PREMISSION);
            }
        }
        else if (Engine.GetState() == DEMO)
        {
            try
            {
                Engine.DemoLoop();
            }
            catch (NotImplementedException& e)
            {
                Engine.ResetToTitle();
            }
        }
        else if (Engine.GetState() == PREMISSION)
        {
            try
            {
                Engine.PreMissionLoop();
            }
            catch (NotImplementedException& e)
            {
                cout << e.what() << endl;
                Engine.SetState(MISSION);
            }
        }
        else if (Engine.GetState() == MISSION)
        {
            try
            {
                Engine.MissionLoop();
            }
            catch (NotImplementedException& e)
            {
                cout << e.what() << endl;
                Engine.SetState(TITLE);
            }

            //Secondary input loop
            if (Engine.mission->Actors.at(0)->controlsLocked == false)
            {
                if (((!keyboard[SDL_SCANCODE_W]) && (!keyboard[SDL_SCANCODE_S])) || ((keyboard[SDL_SCANCODE_W]) && (keyboard[SDL_SCANCODE_S])) || ((SDL_JoystickGetAxis(gamepad, 1) > -10000) && (SDL_JoystickGetAxis(gamepad, 1) < 10000)))
                {
                    Engine.mission->Actors.at(0)->yspeed = 0;
                }
                if (((!keyboard[SDL_SCANCODE_A]) && (!keyboard[SDL_SCANCODE_D])) || ((keyboard[SDL_SCANCODE_A]) && (keyboard[SDL_SCANCODE_D])) || ((SDL_JoystickGetAxis(gamepad, 0) > -10000) && (SDL_JoystickGetAxis(gamepad, 0) < 10000)))
                {
                    Engine.mission->Actors.at(0)->xspeed = 0;
                }

                if ((keyboard[SDL_SCANCODE_W]) || (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_UP) || (SDL_JoystickGetAxis(gamepad, 1) <= -10000))
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.y - 5 >= 0)
                        Engine.mission->Actors.at(0)->yspeed = -5;
                    else
                        Engine.mission->Actors.at(0)->yspeed = 0;
                }
                if ((keyboard[SDL_SCANCODE_S]) || (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_DOWN) || (SDL_JoystickGetAxis(gamepad, 1) >= 10000))
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.y + 5 <= screenheight-150)
                        Engine.mission->Actors.at(0)->yspeed = 5;
                    else
                        Engine.mission->Actors.at(0)->yspeed = 0;
                }

                if ((keyboard[SDL_SCANCODE_A]) || (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_LEFT) || (SDL_JoystickGetAxis(gamepad, 0) <= -10000))
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.x - 5 >= 0)
                        Engine.mission->Actors.at(0)->xspeed = -5;
                    else
                        Engine.mission->Actors.at(0)->xspeed = 0;
                }
                if ((keyboard[SDL_SCANCODE_D]) || (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_RIGHT) || (SDL_JoystickGetAxis(gamepad, 0) >= 10000))
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.x + 5 <= screenwidth*7/10)
                        Engine.mission->Actors.at(0)->xspeed = 5;
                    else
                        Engine.mission->Actors.at(0)->xspeed = 0;
                }

                //Specific to joysticks
                if (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_LEFTUP)
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.x - 5 >= 0)
                        Engine.mission->Actors.at(0)->xspeed = -5;
                    else
                        Engine.mission->Actors.at(0)->xspeed = 0;

                    if (Engine.mission->Actors.at(0)->sprite->rect.y - 5 >= 0)
                        Engine.mission->Actors.at(0)->yspeed = -5;
                    else
                        Engine.mission->Actors.at(0)->yspeed = 0;
                }
                if (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_RIGHTUP)
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.x + 5 <= screenwidth*7/10)
                        Engine.mission->Actors.at(0)->xspeed = 5;
                    else
                        Engine.mission->Actors.at(0)->xspeed = 0;

                    if (Engine.mission->Actors.at(0)->sprite->rect.y - 5 >= 0)
                        Engine.mission->Actors.at(0)->yspeed = -5;
                    else
                        Engine.mission->Actors.at(0)->yspeed = 0;
                }
                if (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_LEFTDOWN)
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.x - 5 >= 0)
                        Engine.mission->Actors.at(0)->xspeed = -5;
                    else
                        Engine.mission->Actors.at(0)->xspeed = 0;

                    if (Engine.mission->Actors.at(0)->sprite->rect.y + 5 <= screenheight-150)
                        Engine.mission->Actors.at(0)->yspeed = 5;
                    else
                        Engine.mission->Actors.at(0)->yspeed = 0;
                }
                if (SDL_JoystickGetHat(gamepad, 0) == SDL_HAT_RIGHTDOWN)
                {
                    if (Engine.mission->Actors.at(0)->sprite->rect.x + 5 <= screenwidth*7/10)
                        Engine.mission->Actors.at(0)->xspeed = 5;
                    else
                        Engine.mission->Actors.at(0)->xspeed = 0;

                    if (Engine.mission->Actors.at(0)->sprite->rect.y + 5 <= screenheight-150)
                        Engine.mission->Actors.at(0)->yspeed = 5;
                    else
                        Engine.mission->Actors.at(0)->yspeed = 0;
                }
            }

            //Now we shoot stuff
            if ((keyboard[SDL_SCANCODE_SPACE]) || (SDL_JoystickGetButton(gamepad, 0)))
            {
                if ((Engine.currentframe >= Engine.mission->Actors.at(0)->lastShot + Engine.mission->Actors.at(0)->shotCooldownTimer) && (!Engine.mission->Actors.at(0)->shotsLocked))
                {
                    if (Engine.mission->Actors.at(0)->activeShots <= Engine.mission->Actors.at(0)->maxShots)
                    {
                        Mix_PlayChannel(-1, lazer, 0);
                        Engine.mission->Actors.at(0)->Shoot(Engine.renderer, Engine.currentframe, &Engine.mission->Actors);
                    }
                }
            }
        }
        else if (Engine.GetState() == NAMEENTRY)
        {
            try
            {
                Engine.NameEntryLoop();
            }
            catch (NotImplementedException& e)
            {
                cout << e.what() << endl;
                Engine.SetState(TITLE);
            }
        }

        //TEST AREA
        if (!Engine.levelready)
        {
            if (Engine.state == TITLE)
            {
                Engine.StartGame();
            }
            else
            {
                Engine.ChangeLevel();
            }
        }
        //END TEST AREA

        /*FPS STUFF. DO NOT ATTEMPT TO MODIFY THIS. I'M SERIOUS.*/
        //No, I have no idea why it reports the wrong values. Help appreciated
        if (Engine.timer.GetSeconds() > 0)
        {
            if (fpsdisplay)
            {
                if (tx_fps != NULL)
                    SDL_DestroyTexture(tx_fps);

                fps = ceil(Engine.currentframe / Engine.timer.GetSeconds());
                tx_fps = TextureFromText(Engine.renderer, "FPS:" + std::to_string(fps), 18);

                SDL_QueryTexture(tx_fps, NULL, NULL, &rect_fps.w, &rect_fps.h);
            }
            Engine.timer.seconds = Engine.timer.GetSeconds();
        }

        if (fpsdisplay)
            SDL_RenderCopy(Engine.renderer, tx_fps, NULL, &rect_fps);
        /*FPS STUFF ENDS HERE.*/

        SDL_SetRenderDrawColor(Engine.renderer, 0,0,0,255);
        SDL_SetRenderTarget(Engine.renderer, NULL);
        SDL_RenderCopy(Engine.renderer, Engine.scene, NULL, NULL);
        SDL_RenderPresent(Engine.renderer);
        ++Engine.currentframe;
    }

    if (gamepad != NULL)
        SDL_JoystickClose(0);

    return 0;
}
