#include "Engine.h"

NoNameEngine::NoNameEngine(SDL_Window* window, int window_width, int window_height)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    state = INTRO;
    levelready = true;
    currentframe = 0;
    level = 1;
    credits = 0;

    SDL_GetRendererOutputSize(renderer, &res_w, &res_h);

    introsequence = new Intro(renderer);
    introsequence->Prime(renderer);

    mainmenu = new Menu(renderer);
    mainmenu->Prime(renderer);

    demo = new Demo(renderer);
    demo->Load(renderer, res_w);

    mission = new Mission(renderer);
    mission->Load(renderer, level);

    nameentry = new NameEntry();
    nameentry->Load();

    scene = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, window_width, window_height);

    //Create the veil
    veil = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, window_width, window_height);
    fade = 1;
    SDL_SetTextureBlendMode(veil, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, veil);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderTarget(renderer, scene);   //For safety's sake. IntroLoop resets it anyway, but it can't hurt
}
NoNameEngine::~NoNameEngine()
{
    //This being called is usually the sign of absolute catastrophic failure.
    introsequence->~Intro();
    delete introsequence;
    mainmenu->~Menu();
    delete mainmenu;
}

ENGINE_STATE NoNameEngine::GetState()
{
    return state;
}
void NoNameEngine::SetState(ENGINE_STATE nstate)
{
    state = nstate;
}

void NoNameEngine::Fade()
{
    uint8_t currentalpha, newalpha;
    SDL_GetTextureAlphaMod(veil, &currentalpha);

    if (fade)
    {
        if (currentalpha - 255/60 >= 0)
            newalpha = currentalpha - 255/60;
        else
            newalpha = 0;
    }
    else if (!fade)
    {
        if (currentalpha + 255/60 <= 255)
            newalpha = currentalpha + 255/60;
        else
            newalpha = 255;
    }

    SDL_SetTextureAlphaMod(veil, newalpha);
}
void NoNameEngine::FadeOut()
{
    fade = false;
}
void NoNameEngine::FadeIn()
{
    fade = true;
}

void NoNameEngine::ModCredits()
{
    SDL_DestroyTexture(mainmenu->gfx[5]->texture);  //Free the god damned thing before writing to it
    if (strlen(std::to_string(credits).c_str()) == 1)
        mainmenu->text_strings[3] = "CREDITS 0" + std::to_string(credits);
    else
        mainmenu->text_strings[3] = "CREDITS " + std::to_string(credits);
    mainmenu->gfx[5]->texture = TextureFromTextShaded(renderer, mainmenu->text_strings[3]);

    if (state == DEMO)
        ResetToTitle();
}

void NoNameEngine::StartGame()
{
    Uint8 veilopacity;
    SDL_GetTextureAlphaMod(veil, &veilopacity);

    mission->Actors.clear();

    if (veilopacity >= 255)
    {
        mission->Load(renderer, 1);
        SetState(MISSION);
        mainmenu->Unload();
        nameentry->Unload();

        if (mission->currentlevel != nullptr)
        {
            std::cout << "Loaded level " << level << std::endl;
            currentframe = 0;
            if (!freeplay)
            {
                credits--;
                ModCredits();
            }
            timer.zero();
            levelready = true;
            FadeIn();
        }
        else
        {
            std::cout << "Something is wrong with the level loading" << std::endl;
        }
    }
}

void NoNameEngine::ChangeLevel()
{
    Uint8 veilopacity;
    SDL_GetTextureAlphaMod(veil, &veilopacity);

    if (veilopacity >= 255)
    {
        mission->Load(renderer, level);

        if (mission->currentlevel != nullptr)
        {
            std::cout << "Loaded level " << level << std::endl;
            currentframe = 0;
            timer.zero();
            levelready = true;
            FadeIn();
        }
        else
        {
            std::cout << "Something is wrong with the level loading" << std::endl;
        }
    }
}

void NoNameEngine::ResetToTitle()
{
    currentframe = 0;
    timer.zero();
    level = 1;
    mainmenu->displaytype = 0;

    demo->Unload();
    nameentry->Unload();
    mission->Unload();
    mainmenu->Load(renderer);

    for (unsigned int i = 1; i < 6; i++)
    {
        mainmenu->gfx[i]->alpha = 0;
        mainmenu->gfx[i]->AutoAlpha();
    }

    SetState(TITLE);
}

void NoNameEngine::FullReset()
{
    //Essentially this is the same function as the constructor, but does not run the risk of crashing the game when re-instancing the engine itself
    //That being said, it's bugged as hell. Prefer ResetToTitle() when possible
    state = INTRO;
    currentframe = 0;
    level = 1;
    score = 0;
    credits = 0;

    timer = Timer();

    //Unload EVERYTHING
    introsequence->Unload();
    introsequence->~Intro();
    delete introsequence;

    mainmenu->Unload();
    SDL_DestroyTexture(mainmenu->gfx[0]->texture);
    mainmenu->~Menu();
    delete mainmenu;

    demo->Unload();
    demo->~Demo();
    delete demo;

    mission->Unload();
    mission->~Mission();
    delete mission;

    if (nameentry->line[0] != NULL)
        nameentry->Unload();
    nameentry->~NameEntry();
    delete nameentry;

    //Then sequentially reset everything as it once was
    introsequence = new Intro(renderer);
    introsequence->Prime(renderer);

    mainmenu = new Menu(renderer);
    mainmenu->Prime(renderer);

    demo = new Demo(renderer);
    demo->Load(renderer, res_w);

    nameentry = new NameEntry();
    nameentry->Load();

    mission = new Mission();
    mission->Load(renderer, 1);

    SDL_DestroyTexture(scene);

    int renderer_buf_w, renderer_buf_h;
    SDL_GetRendererOutputSize(renderer, &renderer_buf_w, &renderer_buf_h);
    scene = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, renderer_buf_w, renderer_buf_h);
}
