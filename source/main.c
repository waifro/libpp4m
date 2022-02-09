#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pp4m/pp4m.h"
#include "pp4m/pp4m_io.h"
#include "pp4m/pp4m_image.h"
#include "pp4m/pp4m_ttf.h"
#include "pp4m/pp4m_draw.h"

#define OPENSANS_REGULAR "resources/ttf/OpenSans-Regular.ttf"

SDL_Window *global_window = NULL;
SDL_Renderer *global_renderer = NULL;
SDL_Texture *background = NULL;

int win_width = 1280;
int win_heigth = 720;

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;

    global_renderer = pp4m_Init(global_window, "pp4m_demo v0.04a", win_width, win_heigth, WINDOW);

    background = pp4m_IMG_ImageToTexture(global_renderer, background, "resources/images/wallpaper.png", 0, 0, 0, 0, 0);

    PP4M_SDL Title;
    pp4m_TTF_MEM_TextureFont(global_renderer, &Title, "Welcome!", OPENSANS_REGULAR, 24, (640 - 50), (360 - 23), PP4M_WHITE);

    PP4M_SDL Info;
    pp4m_TTF_MEM_TextureFont(global_renderer, &Info, "Testing a string!", OPENSANS_REGULAR, 20, (640 - 50 - 25), (360 - 23 - 50), PP4M_WHITE);

    PP4M_SDL Rainbow;
    Rainbow.color = PP4M_WHITE;
    Rainbow.texture = pp4m_DRAW_TextureInitColor(global_renderer, Rainbow.color, &Rainbow.rect, (win_width / 2 - 150), (win_heigth / 2 - 75), 300, 150);

    PP4M_SDL DateAndTime;
    pp4m_TTF_MEM_TextureFont(global_renderer, &DateAndTime, DateAndTime.text, OPENSANS_REGULAR, 30, 1, (win_width - 355), PP4M_WHITE);

    // pp4m_TTF_TextureFont deprecated (memory segfault)

    int red_stats = 0, green_stats = 0, blue_stats = 0;

    PP4M_SDL Framerate;
    Framerate.color = PP4M_YELLOW;
    int frame = 0; int count = 0;

    SDL_Event event;
    while(1) {

        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) break;
        if( event.type == SDL_QUIT ) break;

        frame = pp4m_Framerate();

        if (pp4m_SecondsTick() != count) {
            sprintf(Framerate.text, "%d", frame);

            pp4m_GetDateAndTime(DateAndTime.text);
            pp4m_TTF_MEM_TextureFont(global_renderer, &Framerate, Framerate.text, OPENSANS_REGULAR, 16, 1, 1, Framerate.color);
            count ^= 1;
        }

        SDL_SetTextureColorMod(Rainbow.texture, Rainbow.color.r, Rainbow.color.g, Rainbow.color.b);

        pp4m_TTF_MEM_TextureFont(global_renderer, &DateAndTime, DateAndTime.text, OPENSANS_REGULAR, 30, 1, (win_width - 355), PP4M_WHITE);

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
            else if (green_stats == 0 && Rainbow.color.b < 255 && Rainbow.color.r <= 0) green_stats = -1;
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

        SDL_RenderClear(global_renderer);
        SDL_RenderCopy(global_renderer, background, NULL, NULL);
        SDL_RenderCopy(global_renderer, Rainbow.texture, NULL, &Rainbow.rect);
        SDL_RenderCopy(global_renderer, Title.texture, NULL, &Title.rect);
        SDL_RenderCopy(global_renderer, Info.texture, NULL, &Info.rect);
        SDL_RenderCopy(global_renderer, DateAndTime.texture, NULL, &DateAndTime.rect);
        SDL_RenderCopy(global_renderer, Framerate.texture, NULL, &Framerate.rect);

        SDL_RenderPresent(global_renderer);

    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(Rainbow.texture);
    SDL_DestroyTexture(Title.texture);
    SDL_DestroyTexture(Info.texture);
    SDL_DestroyTexture(Framerate.texture);
    SDL_DestroyTexture(DateAndTime.texture);

    pp4m_Quit(global_window, global_renderer);

    return 0;
}
