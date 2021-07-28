/* Private Project Four Me */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "pp4m.h"
#include "pp4m_ttf.h"

void pp4m_TTF_Init(void) {

    TTF_Init();

    return;

}

void pp4m_TTF_Quit(void) {

    TTF_Quit();

    return;

}

void pp4m_TTF_MEM_TextureFont(SDL_Renderer *renderer, PP4M_SDL *st, const char *text, const char *path, int point, float x, float y, SDL_Color color) {

	PP4M_SDL pd;
	pd.font = TTF_OpenFont(path, point);

	SDL_Surface *surface = TTF_RenderText_Blended(pd.font, text, color);
	pd.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(pd.texture, NULL, NULL, &pd.rect.w, &pd.rect.h);

	pd.rect.y = y; // vertical point
	pd.rect.x = x; // horizontal point

	memcpy(st, &pd, sizeof(pd));

	return;
}

SDL_Texture *pp4m_TTF_TextureFont(SDL_Renderer *renderer, SDL_Texture *texture, char filename[256], SDL_Color color, int point, SDL_Rect *dst, float x, float y, char text[1024]) {

    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    TTF_Font *font = NULL;

    font = TTF_OpenFont(filename, point);

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    dst->x = x;
    dst->y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst->w, &dst->h);

    return texture;

}

/* 2021 @richardwaifro */
