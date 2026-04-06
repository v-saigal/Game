#include "LUtil.h"
#include <SDL3/SDL_log.h>
#include <SDL3_image/SDL_image.h>

bool initSDL(SDL_Window** outWindow,
    SDL_Renderer** outRenderer,
    int width,
    int height,
    const char* title)
{
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(
        title,
        width,
        height,
        0,
        outWindow,
        outRenderer) == false)
    {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}
void closeSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}