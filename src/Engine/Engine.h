#ifndef _ENGINE_H
#define _ENGINE_H

#include "../Entities/Entities.h"
#include "../Levels/LevelTemplate.h"

class Timer
{
public:
    Timer();
    ~Timer(); //You shouldn't have to call this, ever
    void zero();
    uint32_t GetSeconds();

    uint32_t startedOnTick;
    uint32_t seconds = 0;
};

class Intro
{
public:
    Intro(SDL_Renderer* renderer);
    Intro();
    ~Intro();

    //ShadedText* gfx[1];
    UIElement* gfx[1];

    void Prime(SDL_Renderer* renderer);
    void Unload();
};

class Menu
{
public:
    Menu(SDL_Renderer* renderer);
    Menu();
    ~Menu();
    void Prime(SDL_Renderer* renderer);
    void Load(SDL_Renderer* renderer);
    void Unload();

    std::string text_strings[4];
    /*SDL_Texture* text_textures[4];
    SDL_Rect text_rect[4];
    unsigned short text_alpha[4];*/
    Gfx* gfx[6];

    bool displaytype;
};

class Demo
{
public:
    Demo(SDL_Renderer* renderer);
    Demo();
    ~Demo();

    void Load(SDL_Renderer* renderer, int w_width);
    void Unload();

    /*std::string demo_text[2];
    SDL_Texture* demo_texture[2];
    SDL_Rect demo_rect[2];
    unsigned short demo_alpha;*/

    Gfx* gfx[2];
};

class Mission
{
public:
    Mission(SDL_Renderer* renderer);
    Mission();
    ~Mission();

    void Load(SDL_Renderer* renderer, int levelindex);
    void Unload();

    Level* currentlevel;

    std::vector<Actor*> Actors;
};

class NameEntry
{
public:
    NameEntry();
    ~NameEntry();

    std::map<int, std::string, std::greater<int>> scoreboard;

    SDL_Texture* line[5];
    SDL_Rect linerect[5];

    void Load();                            //Reads from file into the scoreboard
    void Unload();                          //Removes scoreboard from memory. Also deletes textures if needed
    void PrintToConsole();                  //Prints scoreboard to stdout, NOT SDL
    void Read(SDL_Renderer* renderer);      //Turns the scoreboard into SDL textures
    void Write(int nscore, std::string nname);                           //Self-explanatory
};

class NoNameEngine
{
public:
    //Your friends, the attributes
    SDL_Renderer* renderer;     //Your new best friend
    int level;                 //Self explanatory
    unsigned int score;         //Same
    char credits;               //Ditto
    int res_w, res_h;           //Internal engine renderer resolution
    uint32_t currentframe;      //Keeping track of time
    Timer timer;                //Ditto, but in a more human manner (seconds vs frames rendered)
    SDL_Texture* scene;         //Where we render everything
    ENGINE_STATE state;         //What we should be rendering

    //A veil to hide stuff and/or ease transitions
    SDL_Texture* veil;
    bool fade;  //0 is out, 1 is in

    //The different machine states, expressed as classes
    Intro* introsequence;
    Menu* mainmenu;
    Demo* demo;
    Mission* mission;
    NameEntry* nameentry;

    //Level loading utilities
    bool levelready;
    void StartGame();
    void ChangeLevel(); //Same method as StartGame, but does not unload the menu (which by that point should already be unloaded)

    //The usual suspects
    NoNameEngine(SDL_Window* window, int window_width, int window_height);
    ~NoNameEngine();

    //The engine loops
    void IntroLoop();
    void NoIntroLoop(); //Just in case
    void MainMenuLoop();
    void DemoLoop();
    void PreMissionLoop();
    void MissionLoop();
    void NameEntryLoop();

    //State accessors (not really needed)
    ENGINE_STATE GetState();
    void SetState(ENGINE_STATE nstate);

    //Love it or hate it
    void Render();
    void CollisionDetection();
    void GarbageCollector();

    //Misc
    void FadeOut();
    void FadeIn();
    void Fade();
    void ModCredits();  //Re-generates the texture for the amount of available credits
    void ResetToTitle();
    void FullReset();
};

#endif // _ENGINE_H
