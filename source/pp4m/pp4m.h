/* Private Project Four Me */

#ifndef _PP4M_H
#define _PP4M_H

extern SDL_Color PP4M_BLACK;
extern SDL_Color PP4M_WHITE;

extern SDL_Color PP4M_RED;
extern SDL_Color PP4M_GREEN;
extern SDL_Color PP4M_BLUE;

extern SDL_Color PP4M_YELLOW;
extern SDL_Color PP4M_PINK;
extern SDL_Color PP4M_CYAN;

SDL_Renderer *pp4m_Init(SDL_Window *window, char title[256], int width, int height);
void pp4m_Quit(void);

#endif // _PP4M_H
