#include "Engine.h"

void NoNameEngine::DrawHUD()
{
    if (hud != NULL)
        SDL_DestroyTexture(hud);

    if (mission->Actors.at(0)->sprite->rect.y < 720*3/10)
    {
        hudrect.y = 720 - hudrect.h;
    }
    else if ((mission->Actors.at(0)->sprite->rect.y > 720*3/10) && (mission->Actors.at(0)->sprite->rect.y < 720*7/10 - 50))
    {
        if (hudrect.y == 0)
        {
            hudrect.y = 0;
        }
        else
        {
            hudrect.y = 720 - hudrect.h;
        }
    }
    else if (mission->Actors.at(0)->sprite->rect.y > 720*7/10 - 50)
    {
        hudrect.y = 0;
    }

    hud = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, hudrect.w, hudrect.h);

    SDL_SetRenderTarget(renderer, hud);
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(renderer, NULL);

    std::string hud_score = std::to_string(score);

    while (hud_score.length() < 6)
    {
        hud_score.insert(hud_score.begin(), '0');
    }

    //Actually drawing all that shit

    Text* buf_stext = new Text(renderer, "SCORE", 255, hudrect.h/4);
    Text* buf_score = new Text(renderer, hud_score.c_str(), 255, hudrect.h/4);
    Text* buf_ltext = new Text(renderer, "1UP", 255, hudrect.h/4);
    Text* buf_lives = new Text(renderer, std::to_string(lives).c_str(), 255, hudrect.h/4);

    buf_stext->rect.x = hudrect.w * 1/3 - buf_stext->rect.w/2;
    buf_score->rect.x = buf_stext->rect.x + buf_stext->rect.w/2 - buf_score->rect.w/2;

    buf_stext->rect.y = hudrect.h * 1/3 - buf_stext->rect.h/2;
    buf_score->rect.y = buf_stext->rect.y + buf_stext->rect.h + 5;

    buf_ltext->rect.x = hudrect.w * 2/3 - buf_ltext->rect.w/2;
    buf_lives->rect.x = buf_ltext->rect.x + buf_ltext->rect.w/2 - buf_lives->rect.w/2;

    buf_ltext->rect.y = hudrect.h * 1/3 - buf_ltext->rect.h/2;
    buf_lives->rect.y = buf_ltext->rect.y + buf_ltext->rect.h + 5;

    SDL_RenderCopy(renderer, buf_stext->texture, NULL, &buf_stext->rect);
    SDL_RenderCopy(renderer, buf_ltext->texture, NULL, &buf_ltext->rect);
    SDL_RenderCopy(renderer, buf_score->texture, NULL, &buf_score->rect);
    SDL_RenderCopy(renderer, buf_lives->texture, NULL, &buf_lives->rect);

    //Free all the things
    SDL_DestroyTexture(buf_stext->texture);
    SDL_DestroyTexture(buf_score->texture);
    SDL_DestroyTexture(buf_ltext->texture);
    SDL_DestroyTexture(buf_lives->texture);

    delete buf_stext;
    delete buf_score;
    delete buf_ltext;
    delete buf_lives;

    SDL_SetRenderTarget(renderer, scene);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderCopy(renderer, hud, NULL, &hudrect);
}
