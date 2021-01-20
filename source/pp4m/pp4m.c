/* Private Project Four Me */

#include <SDL2/SDL.h>

#include "pp4m.h"
#include "pp4m_image.h"
#include "pp4m_ttf.h"

SDL_Color PP4M_BLACK = {0, 0, 0, 255};
SDL_Color PP4M_WHITE = {255, 255, 255, 255};

SDL_Color PP4M_RED = {255, 0, 0, 255};
SDL_Color PP4M_GREEN = {0, 255, 0, 255};
SDL_Color PP4M_BLUE = {0, 0, 255, 255};

SDL_Color PP4M_YELLOW = {255, 255, 0, 255};
SDL_Color PP4M_PINK = {255, 0, 255, 255};
SDL_Color PP4M_CYAN = {0, 255, 255, 255};

SDL_Renderer *pp4m_Init(SDL_Window *window, char title[256], int width, int height) {

    SDL_Init(SDL_INIT_EVERYTHING);
    pp4m_IMG_Init();
    pp4m_TTF_Init();

    SDL_Renderer *renderer = NULL;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    return renderer;

}


void pp4m_Quit(void) {

    pp4m_TTF_Quit();
    pp4m_IMG_Quit();
    SDL_Quit();

    return;

}
