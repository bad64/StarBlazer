#ifndef _LEVEL_TEMPLATE_H
#define _LEVEL_TEMPLATE_H

#include "../Entities/Entities.h"

class Level
{
public:
    Level(int nid);
    Level();
    ~Level();

    static int g_levelid;
    int levelid;
    void Load(SDL_Renderer* renderer);
    void Unload();

    Mix_Music* bgm;

    /*
    Engine topology goes like this:
    Layer 0: HUD. Not a Level element, that's for Mission to handle (at least for now)
    Layer 1: foreground layer. Will probably use Sprites instead of Backgrounds. Might end up unused until I can spawn what I want -when I want it to spawn- on it
    Layer 2: Sprite layer. Not the Level's concern either
    Layer 3: first Background layer. Should scroll faster than layer 4
    Layer 4: second Background layer

    Draw order (obviously) goes bottom to top, aka 4-3-2-1-0.
    */

    Background* layer4[2];
    Background* layer3[2];

    virtual void ReadScript(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
};

class Level1 : public Level
{
public:
    Level1(int nid);
    ~Level1();

    void ReadScript(SDL_Renderer* renderer, int currentframe, std::vector<Actor*> *Actors);
};

#endif // _LEVEL_TEMPLATE_H
