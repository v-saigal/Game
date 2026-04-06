#include "TileMap.h"
#include "LConst.h"

TileMap::TileMap(LTexture& mapTexture) : mapTexture(mapTexture) {}

SDL_FRect TileMap::selectTile(LocationType lType) const
{
    SDL_FRect tile = { 0.0f, 0.0f, 32.0f, 32.0f };
    tile.y = float(lType) * 32.0f;
    return tile;
}

void TileMap::render(int _x, int _y, LocationType lType)
{
    SDL_FRect tile = selectTile(lType);
    float x = kTileMapWidth * float(_x);
    float y = kTileMapHeight * float(_y);
    mapTexture.render(x, y, &tile);
}