#pragma once
#include <SDL3/SDL.h>

// Initialize SDL and create a window + renderer
// Returns true if successful
bool initSDL(SDL_Window** outWindow, SDL_Renderer** outRenderer, int width, int height, const char* title);

// Clean up SDL window and renderer
void closeSDL(SDL_Window* window, SDL_Renderer* renderer);