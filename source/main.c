#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pp4m/pp4m.h"
#include "pp4m/pp4m_io.h"
#include "pp4m/pp4m_image.h"
#include "pp4m/pp4m_ttf.h"
#include "pp4m/pp4m_draw.h"

SDL_Window *global_window = NULL;
SDL_Renderer *global_renderer = NULL;
SDL_Texture *background = NULL;

int win_width = 1280;
int win_heigth = 720;

int main(int argc, char *argv[]) {

    global_renderer = pp4m_Init(global_window, "pp4m_demo v0.02a", win_width, win_heigth);

    background = pp4m_IMG_ImageToRenderer(global_renderer, "resources/images/wallpaper.png", 0, 0, 0, 0, 0);

    PP4M_SDL Title;
    Title.texture = pp4m_TTF_TextureFont(global_renderer, "resources/ttf/OpenSans-Regular.ttf", PP4M_WHITE, 24, &Title.rect, (640 - 50), (360 - 23), "Welcome!");

    PP4M_SDL Rainbow;
    Rainbow.color = PP4M_WHITE;
    Rainbow.texture = pp4m_DRAW_TextureRect(global_renderer, Rainbow.color, &Rainbow.rect, (win_width / 2 - 150), (win_heigth / 2 - 75), 300, 150);

    PP4M_SDL DateAndTime;

    bool quit = false;

    int red_stats = 0, green_stats = 0, blue_stats = 0;

    while(!quit) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                if( event.type == SDL_QUIT ) quit = true;
        }

        SDL_SetTextureColorMod(Rainbow.texture, Rainbow.color.r, Rainbow.color.g, Rainbow.color.b);

        if (Rainbow.color.r >= 255) {
            if (red_stats == 1 && Rainbow.color.b <= 0) red_stats = 0;
            else if (red_stats == 0 && Rainbow.color.b >= 255 && Rainbow.color.g >= 255) red_stats = -1;
        }
        else if (Rainbow.color.r <= 0) {
            if (red_stats == -1) red_stats = 0;
            else if (red_stats == 0 && Rainbow.color.g <= 0 && Rainbow.color.b <= 0) red_stats = 1;
        }

        if (Rainbow.color.g >= 255) {
            if (green_stats == 1) green_stats = 0;
            else if (green_stats == 0 && Rainbow.color.b <= 255 && Rainbow.color.r <= 0) green_stats = -1;
        }
        else if (Rainbow.color.g <= 0) {
            if (green_stats == -1) green_stats = 0;
            else if (green_stats == 0 && Rainbow.color.r >= 255 && Rainbow.color.b <= 0) green_stats = 1;
        }

        if (Rainbow.color.b >= 255) {
            if (blue_stats == 1) blue_stats = 0;
            else if (blue_stats == 0 && Rainbow.color.r <= 0 && Rainbow.color.g <= 0) blue_stats = -1;
        }
        else if (Rainbow.color.b <= 0) {
            if (blue_stats == -1) blue_stats = 0;
            else if (blue_stats == 0 && Rainbow.color.g >= 255 && Rainbow.color.r >= 255) blue_stats = 1;
        }

        if (red_stats == 1) Rainbow.color.r += 1;
        else if (red_stats == -1) Rainbow.color.r -= 1;

        if (green_stats == 1) Rainbow.color.g += 1;
        else if (green_stats == -1) Rainbow.color.g -= 1;

        if (blue_stats == 1) Rainbow.color.b += 1;
        else if (blue_stats == -1) Rainbow.color.b -= 1;

        pp4m_GetDateAndTime(DateAndTime.text);
        DateAndTime.texture = pp4m_TTF_TextureFont(global_renderer, "resources/ttf/OpenSans-Regular.ttf", PP4M_WHITE, 30, &DateAndTime.rect, (win_width - 348), 1,  DateAndTime.text);

        SDL_RenderClear(global_renderer);
        SDL_RenderCopy(global_renderer, background, NULL, NULL);
        SDL_RenderCopy(global_renderer, Rainbow.texture, NULL, &Rainbow.rect);
        SDL_RenderCopy(global_renderer, Title.texture, NULL, &Title.rect);
        SDL_RenderCopy(global_renderer, DateAndTime.texture, NULL, &DateAndTime.rect);
        SDL_RenderPresent(global_renderer);

        // needs to improve deleting memory (workaround)
        SDL_DestroyTexture(DateAndTime.texture);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(Rainbow.texture);
    SDL_DestroyTexture(Title.texture);
    SDL_DestroyTexture(DateAndTime.texture);

    SDL_DestroyRenderer(global_renderer);
    SDL_DestroyWindow(global_window);

    pp4m_Quit();

    return 0;
}
