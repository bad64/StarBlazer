#include "Engine.h"

void Demo::Load(SDL_Renderer* renderer, int w_width)
{
    int r_width, r_height;
    SDL_GetRendererOutputSize(renderer, &r_width, &r_height);

    gfx[0]->texture = TextureFromTextShaded(renderer, "IN THE YEAR A.D. 21XX, AN INTERGALACTIC TURF WAR BETWEEN HUMANS AND THE INSECTOID XYZZY STARTED. DURING A DARING ASSAULT BY THE UNITED EARTH MARINES, A LONE SHIP SLIPPED BEHIND ENEMY LINES, TASKED WITH ASSASSINATING THE GENERAL AQILROX, CURRENTLY STATIONED ON THE MOON KRYLLON IV.", 0, 0);
    gfx[1]->texture = TextureFromTextShaded(renderer, "THUS BEGINS THE OPERATION CODENAMED \"STAR BLAZER\"...", 0, 0);

    for (unsigned int i = 0; i < 2; i++)
    {
        gfx[i]->AutoSize();
        gfx[i]->rect.x = r_width/2 - gfx[i]->rect.w/2;
    }

    SDL_GetRendererOutputSize(renderer, NULL, &gfx[0]->rect.y);
    gfx[0]->rect.y += 5;
    gfx[1]->rect.y = gfx[0]->rect.y + gfx[0]->rect.h + 50;
}
void Demo::Unload()
{
    for (unsigned int i = 0; i < 2; i++)
    {
        SDL_DestroyTexture(gfx[i]->texture);
    }
}


Demo::Demo(SDL_Renderer* renderer)
{
    /*demo_text[0] = "IN THE YEAR A.D. 21XX, AN INTERGALACTIC TURF WAR BETWEEN HUMANS AND THE INSECTOID XYZZY STARTED. DURING A DARING ASSAULT BY THE UNITED EARTH MARINES, A LONE SHIP SLIPPED BEHIND ENEMY LINES, TASKED WITH ASSASSINATING THE GENERAL AQILROX, CURRENTLY STATIONED ON THE MOON KRYLLON IV.";
    demo_text[1] = "THUS BEGINS THE OPERATION CODENAMED \"STAR BLAZER\"...";
    demo_alpha = 0;*/

    gfx[0] = new Gfx(renderer, "error");
    gfx[1] = new Gfx(renderer, "error");

    Load(renderer, 1280);
}
Demo::Demo()
{
    /*demo_text[0] = "IN THE YEAR A.D. 21XX, AN INTERGALACTIC TURF WAR BETWEEN HUMANS AND THE INSECTOID XYZZY STARTED.\
                DURING A DARING ASSAULT BY THE UNITED EARTH MARINES, A LONE SHIP SLIPPED BEHIND ENEMY LINES,\
                TASKED WITH ASSASSINATING THE GENERAL AQILROX, CURRENTLY STATIONED ON THE MOON KRYLLON IV.";
    demo_text[1] = "THUS BEGINS THE OPERATION CODENAMED \"STAR BLAZER\"...";
    demo_alpha = 0;*/
}
Demo::~Demo()
{
    /*for (unsigned char i = 0; i < 2; i++)
    {
        SDL_DestroyTexture(gfx[i]->texture);
        delete gfx[i];
    }*/
}

void NoNameEngine::DemoLoop()
{
    SDL_SetRenderTarget(renderer, scene);
    if (currentframe < 60)
    {
        if (demo->gfx[0]->alpha + 255 / 60 <= 255)
            demo->gfx[0]->alpha += 255 / 60;
        else
            demo->gfx[0]->alpha = 255;
    }

    if (currentframe % 2 == 0)
    {
        demo->gfx[0]->rect.y -= 1;
        demo->gfx[1]->rect.y = demo->gfx[0]->rect.y + demo->gfx[0]->rect.h + 50;
    }

    SDL_RenderCopy(renderer, mainmenu->gfx[0]->texture, NULL, NULL);
    SDL_RenderCopy(renderer, demo->gfx[0]->texture, NULL, &demo->gfx[0]->rect);
    SDL_RenderCopy(renderer, demo->gfx[1]->texture, NULL, &demo->gfx[1]->rect);

    if (demo->gfx[1]->rect.y <= -100)
    {
        demo->Unload();
        ResetToTitle();
    }
}
