#include "Engine.h"

void NoNameEngine::Render()
{
    //Draw background
    for (unsigned int j = 0; j < 2; j++)
    {
        mission->currentlevel->layer4[j]->Scroll(renderer);
        mission->currentlevel->layer3[j]->Scroll(renderer);
    }
    mission->currentlevel->layer4[0]->Render(renderer);
    mission->currentlevel->layer4[1]->Render(renderer);
    mission->currentlevel->layer3[0]->Render(renderer);
    mission->currentlevel->layer3[1]->Render(renderer);

    //Draw sprites
    for (unsigned int i = 0; i < mission->Actors.size(); i++)
    {
        if (mission->Actors[i]->doDraw)
        {
            SDL_RenderCopy(renderer, mission->Actors[i]->sprite->texture, &mission->Actors[i]->cliprect, &mission->Actors[i]->sprite->rect);
        }
    }

    //Draw UI

    //Draw veil
    Fade();
    SDL_RenderCopy(renderer, veil, NULL, NULL);
}
