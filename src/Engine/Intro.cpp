#include "Engine.h"

void Intro::Prime(SDL_Renderer* renderer)
{
    gfx[0] = new UIElement(renderer, "lab", 0);
    SDL_GetRendererOutputSize(renderer, &gfx[0]->rect.x, &gfx[0]->rect.y);

    /*if (gfx[0]->rect.y == 1080)
    {
        gfx[0]->rect.w = gfx[0]->rect.h = 700;
    }*/

    gfx[0]->rect.w = gfx[0]->rect.h = (gfx[0]->rect.y * 4)/10;

    gfx[0]->rect.x = (gfx[0]->rect.x/2) - (gfx[0]->rect.w/2);
    gfx[0]->rect.y = (gfx[0]->rect.y/2) - (gfx[0]->rect.h/2);
}
void Intro::Unload()
{
    SDL_DestroyTexture(gfx[0]->texture);
}

Intro::Intro(SDL_Renderer* renderer)
{
    Prime(renderer);
}
Intro::Intro()
{

}
Intro::~Intro()
{
    /*SDL_DestroyTexture(gfx[0]->texture);
    delete gfx[0];*/
}

void NoNameEngine::IntroLoop()
{
    SDL_SetRenderTarget(renderer, scene);

    if (currentframe == 300)
    {
        introsequence->Unload();
        currentframe = 0;
        timer.zero();
        SetState(TITLE);
    }

    if ((currentframe > 60) && (currentframe < 180) && (introsequence->gfx[0]->alpha <= 255))
    {
        if (introsequence->gfx[0]->alpha + 255 / 60 <= 255)
        {
            introsequence->gfx[0]->alpha += 255 / 60;
        }
        else
        {
            introsequence->gfx[0]->alpha = 255;
        }
    }
    if ((currentframe > 180) && (introsequence->gfx[0]->alpha >= 0))
    {
        if (introsequence->gfx[0]->alpha - 255 / 60 >= 0)
        {
            introsequence->gfx[0]->alpha -= 255 / 60;
        }
        else
        {
            introsequence->gfx[0]->alpha = 0;
        }
    }

    introsequence->gfx[0]->SetAlpha(introsequence->gfx[0]->alpha);
    introsequence->gfx[0]->Render(renderer);
}
void NoNameEngine::NoIntroLoop()
{
    currentframe = 0;
    SetState(TITLE);
}
