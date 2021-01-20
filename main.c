#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "pp4m/pp4m.h"
#include "pp4m/pp4m_io.h"
#include "pp4m/pp4m_image.h"
#include "pp4m/pp4m_ttf.h"

SDL_Window *global_window = NULL;
SDL_Renderer *global_renderer = NULL;
SDL_Texture *global_texture = NULL;

int main (int argc, char *argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    global_window = SDL_CreateWindow("n/o", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    global_renderer = SDL_CreateRenderer(global_window, 0, SDL_RENDERER_ACCELERATED);

    pp4m_IMG_Init();
    pp4m_TTF_Init();

    global_texture = pp4m_IMG_ImageToRenderer(global_renderer,
                             "resources/images/wallpaper.png",
                             0, 0, 0, 0, 0);

    SDL_Rect SansRegular_Rect;
    SDL_Texture *SansRegular_Title = NULL;
    SansRegular_Title = pp4m_TTF_TextureFont(global_renderer, "resources/ttf/OpenSans-Regular.ttf", 24, &SansRegular_Rect, 200, 200, "Welcome!");

    bool quit = false;

    while(!quit) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
                if( event.type == SDL_QUIT ) quit = true;
        }

        SDL_RenderClear(global_renderer);
        SDL_RenderCopy(global_renderer, global_texture, NULL, NULL);
        SDL_RenderCopy(global_renderer, SansRegular_Title, NULL, &SansRegular_Rect);
        SDL_RenderPresent(global_renderer);

    }

    SDL_DestroyRenderer(global_renderer);
    SDL_DestroyWindow(global_window);

    pp4m_IMG_Quit();
    pp4m_TTF_Quit();
    SDL_Quit();

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
