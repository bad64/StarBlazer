#include "Engine.h"


void Menu::Prime(SDL_Renderer* renderer)
{
    text_strings[0] = "-INSERT COIN-";
    text_strings[1] = "-PRESS START-";
    text_strings[2] = "GALACTIC HEROES";
    if (!freeplay)
        text_strings[3] = "CREDITS 00";
    else
        text_strings[3] = "FREE PLAY!";

    gfx[0] = new UIElement(renderer, "bg_title", 0);
    gfx[1] = new UIElement(renderer, "title", 0);

    for (unsigned int i = 2; i < 6; i++)
        gfx[i] = new ShadedText(renderer, text_strings[i-2], 0, 0);

    int r_width, r_height;
    //SDL_GetRendererOutputSize(renderer, &r_width, &r_height);
    r_width = 960/2;
    r_height = 720;

    gfx[2]->rect.x = r_width - gfx[2]->rect.w/2;
    gfx[2]->rect.y = (r_height * 3)/4 - gfx[2]->rect.h / 2;

    gfx[3]->rect = gfx[2]->rect;
    gfx[4]->rect = gfx[2]->rect;

    gfx[4]->rect.y = (r_height*1)/6;

    gfx[5]->rect.x = r_width - gfx[5]->rect.w/2;
    gfx[5]->rect.y = r_height - gfx[5]->rect.h - 5;
}
void Menu::Load(SDL_Renderer* renderer)
{
    gfx[1]->texture = LoadInterfaceElement(renderer, "title");
    gfx[2]->texture = TextureFromTextShaded(renderer, text_strings[0], 0, 0);
    gfx[3]->texture = TextureFromTextShaded(renderer, text_strings[1], 0, 0);
}
void Menu::Unload()
{
    for (unsigned int i = 1; i < 3; i++)
        SDL_DestroyTexture(gfx[i]->texture);
}

Menu::Menu(SDL_Renderer* renderer)
{
    Prime(renderer);
    displaytype = 0;
}
Menu::Menu()
{
    displaytype = 0;
}
Menu::~Menu()
{
    /*for (unsigned int i = 0; i < 6; i++)
        SDL_DestroyTexture(gfx[i]->texture);*/
}

void NoNameEngine::MainMenuLoop()   //This is supposed to use the NoNameEngine namespace, do not touch
{
    SDL_SetRenderTarget(renderer, scene);
    bool locked = false;

    //Fading in
    if (currentframe <= 65)
    {
        for (unsigned int i = 0; i < 6; i++)
        {
            if (mainmenu->gfx[i]->alpha + 255/60 <= 255)
                mainmenu->gfx[i]->alpha += 255/60;
            else
                mainmenu->gfx[i]->alpha = 255;
            mainmenu->gfx[i]->AutoAlpha();
        }
    }
    //Fading out
    if (currentframe >= 1440)
    {
        mainmenu->displaytype = 0;  //Force display type
        locked = true;

        for (unsigned int i = 1; i < 6; i++)
        {
            if (mainmenu->gfx[i]->alpha - 255/60 >= 0)
                mainmenu->gfx[i]->alpha -= 255/60;
            else
                mainmenu->gfx[i]->alpha = 0;
            mainmenu->gfx[i]->AutoAlpha();
        }
    }

    //Transitioning between title screen and scoreboard
    if ((currentframe % 300 == 0) && (currentframe > 299))
    {
        if (!locked)
        {
            if (mainmenu->displaytype == 0)
            {
                mainmenu->Unload();
                nameentry->Load();
                nameentry->Read(renderer);

                SDL_QueryTexture(nameentry->line[0], NULL, NULL, &nameentry->linerect[0].w, &nameentry->linerect[0].h);
                nameentry->linerect[0].x = R_WIDTH/2 - nameentry->linerect[0].w/2;
                nameentry->linerect[0].y = (R_HEIGHT*2)/6;

                for (unsigned int i = 1; i < 5; i++)
                {
                    nameentry->linerect[i].x = nameentry->linerect[i-1].x;
                    nameentry->linerect[i].y = nameentry->linerect[i-1].y + nameentry->linerect[i-1].h + 5;
                    nameentry->linerect[i].w = nameentry->linerect[i-1].w;
                    nameentry->linerect[i].h = nameentry->linerect[i-1].h;
                }

                mainmenu->displaytype = 1;
            }
            else
            {
                nameentry->Unload();
                mainmenu->Load(renderer);
                mainmenu->displaytype = 0;
            }
        }
    }

    SDL_RenderCopy(renderer, mainmenu->gfx[0]->texture, NULL, NULL); //Rendering the background

    //Drawing either the title screen or the scoreboard
    if (mainmenu->displaytype == 0)
    {
        SDL_RenderCopy(renderer, mainmenu->gfx[1]->texture, NULL, NULL);

        if (!freeplay)
        {
            if (credits == 0)
                SDL_RenderCopy(renderer, mainmenu->gfx[2]->texture, NULL, &mainmenu->gfx[2]->rect);
            else
                SDL_RenderCopy(renderer, mainmenu->gfx[3]->texture, NULL, &mainmenu->gfx[3]->rect);
        }
        else
        {
            SDL_RenderCopy(renderer, mainmenu->gfx[3]->texture, NULL, &mainmenu->gfx[3]->rect);
        }
    }
    else
    {
        for (unsigned int i = 0; i < 5; i++)
        {
            SDL_RenderCopy(renderer, nameentry->line[i], NULL, &nameentry->linerect[i]);
        }
        SDL_RenderCopy(renderer, mainmenu->gfx[4]->texture, NULL, &mainmenu->gfx[4]->rect);
    }
    //Drawing the credit amount
    SDL_RenderCopy(renderer, mainmenu->gfx[5]->texture, NULL, &mainmenu->gfx[5]->rect);

    //Drawing the veil
    Fade();
    SDL_RenderCopy(renderer, veil, NULL, NULL);

    //Transition to demo screen
    if (currentframe == 1559)
    {
        mainmenu->Unload();
        nameentry->Unload();
        demo->Load(renderer, res_w);
        SetState(DEMO);
    }
}
