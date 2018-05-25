#include "../../includes.h"

Gfx::Gfx(SDL_Renderer* renderer, std::string name, unsigned short nalpha)
{
    alpha = nalpha;
    texture = NULL;

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, nalpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
Gfx::Gfx()
{
    alpha = 255;
    texture = NULL;
}
Gfx::~Gfx()
{
    SDL_DestroyTexture(texture);
}

void Gfx::AutoSize()
{
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
void Gfx::SetAlpha(unsigned short nalpha)
{
    SDL_SetTextureAlphaMod(texture, nalpha);
}
void Gfx::AutoAlpha()
{
    SDL_SetTextureAlphaMod(texture, alpha);
}
void Gfx::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

Sprite::Sprite(SDL_Renderer* renderer, std::string name, unsigned short nalpha) : Gfx(renderer, name, nalpha)
{
    alpha = nalpha;
    texture = LoadTexture(renderer, name);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, nalpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
Sprite::Sprite()
{
    alpha = 255;
    texture = NULL;
}
Sprite::~Sprite()
{
    //SDL_DestroyTexture(texture);
}

Background::Background(SDL_Renderer* renderer, int levelid, std::string name, unsigned short nscrollspeed, unsigned short nalpha) : Gfx(renderer, name, nalpha)
{
    alpha = nalpha;
    texture = LoadBG(renderer, std::to_string(levelid), name);
    scrollspeed = nscrollspeed;

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, nalpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
Background::Background()
{
    alpha = 255;
    texture = NULL;
}
Background::~Background()
{

}
void Background::Scroll(SDL_Renderer* renderer)
{
    rect.x -= scrollspeed;

    if (rect.x <= -rect.w)
    {
        int screenrightboundary;
        SDL_GetRendererOutputSize(renderer, &screenrightboundary, nullptr);
        rect.x = screenrightboundary;
    }
}

UIElement::UIElement(SDL_Renderer* renderer, std::string name, unsigned short nalpha) : Gfx(renderer, name, nalpha)
{
    alpha = nalpha;
    texture = LoadInterfaceElement(renderer, name);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, nalpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
UIElement::UIElement()
{
    alpha = 255;
    texture = NULL;
}
UIElement::~UIElement()
{
    //SDL_DestroyTexture(texture);
}

Text::Text(SDL_Renderer* renderer, std::string text, unsigned short nalpha, int fontsize) : Gfx(renderer, text, nalpha)
{
    alpha = nalpha;
    texture = TextureFromText(renderer, text, fontsize);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, nalpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
Text::Text() : Gfx()
{
    alpha = 255;
    texture = NULL;
}
Text::~Text()
{
    //SDL_DestroyTexture(texture);
}

ShadedText::ShadedText(SDL_Renderer* renderer, std::string text, unsigned short nalpha, int fontsize) : Gfx(renderer, text, nalpha)
{
    alpha = nalpha;
    texture = TextureFromTextShaded(renderer, text, 0, fontsize);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, nalpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
ShadedText::ShadedText() : Gfx()
{
    alpha = 255;
    texture = NULL;

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
ShadedText::~ShadedText()
{
    //SDL_DestroyTexture(texture);
}
