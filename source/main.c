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

int main (int argc, char *argv[]) {

    global_renderer = pp4m_Init(&global_window, "pp4m_demo v0.02a", 1280, 720);

    background = pp4m_IMG_ImageToRenderer(global_renderer, "resources/images/wallpaper.png", 0, 0, 0, 0, 0);

    SDL_Rect SansRegular_Rect;
    SDL_Texture *SansRegular_Title = NULL;
    SansRegular_Title = pp4m_TTF_TextureFont(global_renderer, "resources/ttf/OpenSans-Regular.ttf", 24, &SansRegular_Rect, (640 - 50), (360 - 23), "Welcome!");

    SDL_Rect RainbowRect;
    SDL_Color rainbow = PP4M_BLACK;
    SDL_Texture *RainbowSquare = NULL;

    bool quit = false;

    int red_stats, green_stats, blue_stats;

    red_stats = 1;

    while(!quit) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                if( event.type == SDL_QUIT ) quit = true;
        }

        RainbowSquare = pp4m_DRAW_TextureRect(global_window, global_renderer, rainbow, &RainbowRect, (1280 / 2 - 150), (720 / 2 - 75), 300, 150);

        if (red_stats == 1) rainbow.r += 1;
        else if (red_stats == -1) rainbow.r -= 1;

        if (green_stats == 1) rainbow.g += 1;
        else if (green_stats == -1) rainbow.g -= 1;

        if (blue_stats == 1) rainbow.b += 1;
        else if (blue_stats == -1) rainbow.b -= 1;

        if (rainbow.r >= 255) {
            if (red_stats == 1 && rainbow.b <= 0) red_stats = 0;
            else if (red_stats == 0 && rainbow.b >= 255 && rainbow.g >= 255) red_stats = -1;
        }
        else if (rainbow.r <= 0) {
            if (red_stats == -1) red_stats = 0;
            else if (red_stats == 0) red_stats = 1;
        }

        if (rainbow.g >= 255) {
            if (green_stats == 1) green_stats = 0;
            else if (green_stats == 0 && rainbow.r <= 0 && rainbow.b <= 255) green_stats = -1;
        }
        else if (rainbow.g <= 0) {
            if (green_stats == -1) green_stats = 0;
            else if (green_stats == 0 && rainbow.r >= 255 && rainbow.b <= 0) green_stats = 1;
        }

        if (rainbow.b >= 255) {
            if (blue_stats == 1) blue_stats = 0;
            else if (blue_stats == 0 && rainbow.r <= 0 && rainbow.g <= 0) blue_stats = -1;
        }
        else if (rainbow.b <= 0) {
            if (blue_stats == -1) blue_stats = 0;
            else if (blue_stats == 0 && rainbow.g >= 255 && rainbow.r >= 255) blue_stats = 1;
        }

        SDL_RenderClear(global_renderer);
        SDL_RenderCopy(global_renderer, background, NULL, NULL);
        SDL_RenderCopy(global_renderer, RainbowSquare, NULL, &RainbowRect);
        SDL_RenderCopy(global_renderer, SansRegular_Title, NULL, &SansRegular_Rect);
        SDL_RenderPresent(global_renderer);

    }

    SDL_DestroyRenderer(global_renderer);
    SDL_DestroyWindow(global_window);

    pp4m_Quit();

    return 0;
}

/*                                         Copyright (c) 2021 @richardwaifro //
#                                                                                                                                                    #
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), #
# to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, #
# and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:         #
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.                     #
#                                                                                                                                                    #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,                                                                                    #
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,                                                                #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.                                                                                              #
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,                                                                        #
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,                                                     #
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                                            #
#                                                                                                                                                    #
/#                                         Copyright (c) 2021 @richardwaifro */
