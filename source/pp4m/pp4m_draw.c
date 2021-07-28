/* Private Project Four Me */

#include <SDL2/SDL.h>
#include "pp4m_draw.h"

SDL_Texture *pp4m_DRAW_TextureRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect *rect, float x, float y, float w, float h) {

    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    rect->x = 0;
    rect->y = 0;
    rect->w = (int)w;
    rect->h = (int)h;

    SDL_FillRect(surface, rect, SDL_MapRGB(surface->format, color.r, color.g, color.b));

    rect->x = (int)x;
    rect->y = (int)y;

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    return texture;

}

/* 2021 @richardwaifro */
