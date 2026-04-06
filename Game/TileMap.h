#ifndef TileMap_H
#define TileMap_H

#include <SDL3/SDL.h>
#include "LTexture.h"
#include "LConst.h"

class TileMap
{
public:
    TileMap(LTexture& mapTexture);

    SDL_FRect selectTile(LocationType lType) const;

    void render(int _x, int _y, LocationType lType);  // removed const

private:
    LTexture& mapTexture;  // safer than pointer
};

#endif
