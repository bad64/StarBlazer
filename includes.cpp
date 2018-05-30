#include "includes.h"

using namespace std;

//These are global variables. They are used pretty much everywhere across the board, so this is just easier than passing it through parameters every time
bool debug = false;
bool verbose = false;
bool nointro = false;
bool freeplay = false;
bool fpsdisplay = false;

bool gameover = false;

int screenwidth = 960;
int screenheight = 720;

//This needs to be defined before the engine itself, even though it is basically an engine method
SDL_Texture* LoadTexture(SDL_Renderer* renderer, string texturename)
{
    //Short explanation: With the previous inline loading method, we could not automatically free the memory previously allocated to
    //the SDL_Surface we need to load as a base to convert into a VRAM-usable texture (SDL_Surfaces can't be stored in the VRAM).
    //It may or may not end up saturating the memory on some weaker systems if the game is left to run for extended periods of time,
    //but I'd rather fix that problem preemptively.
    //It was also much harder to handle errors, so all in all, this is a noticeable improvement

    SDL_Surface* t_surface = IMG_Load(string(string("resources/gfx/") + string(texturename) + string(".png")).c_str());

    if (!t_surface)
    {
        cout << "FIXME: Could not load resources/gfx/" << texturename << ".png, defaulting to fallback texture" << endl;
        t_surface = IMG_Load(string("resources/gfx/error.png").c_str());
    }

    SDL_Texture* t_texture = SDL_CreateTextureFromSurface(renderer, t_surface);
    SDL_FreeSurface(t_surface);
    return t_texture;
}

SDL_Texture* LoadInterfaceElement(SDL_Renderer* renderer, string texturename)
{
    SDL_Surface* t_surface = IMG_Load(string( string("resources/ui/") + string(texturename) + string(".png")).c_str());

    if (!t_surface)
    {
        cout << "FIXME: Could not load resources/ui/" << texturename << ".png, defaulting to fallback texture" << endl;
        t_surface = IMG_Load(string("resources/ui/error.png").c_str());
    }

    SDL_Texture* t_texture = SDL_CreateTextureFromSurface(renderer, t_surface);
    SDL_FreeSurface(t_surface);
    return t_texture;
}

SDL_Texture* LoadBG(SDL_Renderer* renderer, string levelfolder, string texturename)
{
    SDL_Surface* t_surface = IMG_Load(string( string("resources/levels/level") + string(levelfolder) + "/" + string(texturename) + string(".png")).c_str());

    if (!t_surface)
    {
        cout << "FIXME: Could not load resources/levels/level/" << texturename << ".png, defaulting to fallback texture" << endl;
        if (texturename == "layer3")
            t_surface = IMG_Load(string("resources/levels/default_layer3.png").c_str());
        else if (texturename == "layer4")
            t_surface = IMG_Load(string("resources/levels/default_layer4.png").c_str());
    }

    SDL_Texture* t_texture = SDL_CreateTextureFromSurface(renderer, t_surface);
    SDL_FreeSurface(t_surface);
    return t_texture;
}

SDL_Texture* TextureFromText(SDL_Renderer* renderer, std::string text, int fontsize)
{
    SDL_Color white = {255,255,255,255};
    SDL_Texture* txbuf = NULL;
    TTF_Font* font = NULL;

    int fontscale;
    SDL_GetRendererOutputSize(renderer, nullptr, &fontscale);
    fontscale = fontscale / 20;

    if (fontsize == 0)
        font = TTF_OpenFont("resources/PressStart2P.ttf", fontscale);
    else
        font = TTF_OpenFont("resources/PressStart2P.ttf", fontsize);

    if (font == NULL)
    {
        std::cout << "Unable to open font file! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        SDL_Surface* srfbuf = TTF_RenderText_Solid(font, text.c_str(), white);

        if (srfbuf == NULL)
        {
            if (!text.empty())
                std::cout << "Unable to render text surface! SDL_TTF Error: " << TTF_GetError() << std::endl;
        }
        else
        {
            txbuf = SDL_CreateTextureFromSurface(renderer, srfbuf);
        }
        SDL_FreeSurface(srfbuf);
    }

    TTF_CloseFont(font);
    font = NULL;    //Safety first
    return txbuf;
}

SDL_Texture* TextureFromTextShaded(SDL_Renderer* renderer, std::string text, unsigned int w_width, int fontsize)
{
    SDL_Color white = {255,255,255,255};
    SDL_Color shadow = {0,60,130,255};
    SDL_Texture* txbuf = NULL;
    TTF_Font* font = NULL;

    int fontscale, r_width;
    SDL_GetRendererOutputSize(renderer, &r_width, &fontscale);
    fontscale = fontscale / 20;

    if (w_width != 0)
        r_width = w_width;

    if (fontsize == 0)
        font = TTF_OpenFont("resources/PressStart2P.ttf", fontscale);
    else
        font = TTF_OpenFont("resources/PressStart2P.ttf", fontsize);

    if (font == NULL)
    {
        std::cout << "Unable to open font file! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    else
    {
        SDL_Surface* srfbuf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), white, (r_width*9)/10);
        SDL_Surface* shdbuf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), shadow, (r_width*9)/10);
        if ((srfbuf == NULL) || (shdbuf == NULL))
        {
            if (!text.empty())
                std::cout << "Unable to render text surface! SDL_TTF Error: " << TTF_GetError() << std::endl;
        }
        else
        {
            SDL_Surface* shadedtext = SDL_CreateRGBSurfaceWithFormat(0, srfbuf->w+2, srfbuf->h+5, 8, SDL_PIXELFORMAT_RGBA8888);

            SDL_Rect srfrect = {0, 0, srfbuf->w, srfbuf->h};
            SDL_Rect shdrect = {2, 5, shdbuf->w, shdbuf->h};

            SDL_BlitSurface(shdbuf, NULL, shadedtext, &shdrect);
            SDL_BlitSurface(srfbuf, NULL, shadedtext, &srfrect);

            SDL_SetColorKey(shadedtext, SDL_TRUE, SDL_MapRGB(shadedtext->format, 0,0,0));

            txbuf = SDL_CreateTextureFromSurface(renderer, shadedtext);
            SDL_FreeSurface(shadedtext);
        }
        SDL_FreeSurface(srfbuf);
        SDL_FreeSurface(shdbuf);
    }

    TTF_CloseFont(font);
    font = NULL;    //Safety first
    return txbuf;
}
