#pragma once

#include <vector>
#include "EntityIntent.h"
#include "Entity.h"
#include "Map.h"
#include <random>
#include <unordered_map>
struct GameState
{
    static constexpr int EMPTY_TILE = -1;

    std::mt19937 gen;
    Map map;
    std::vector<Entity> entities;
    std::vector<int> positionIndex;
    int turnNumber = 0;
    std::unordered_map<int, MoveIntent> intents;
    // Constructor
    GameState(int width, int height, uint32_t seed = 0)
        : gen(seed ? seed : std::random_device{}()),
        map(width, height),
        positionIndex(width* height, EMPTY_TILE)
    {
    }

    // Convert (x,y) to flat index
    int toIndex(int x, int y) const
    {
        return y * map.width + x;
    }

    // Safe accessors
    int entityAt(int x, int y) const
    {
        return positionIndex[toIndex(x, y)];
    }

    void setEntity(int x, int y, int id)
    {
        positionIndex[toIndex(x, y)] = id;
    }

    void clearTile(int x, int y)
    {
        positionIndex[toIndex(x, y)] = EMPTY_TILE;
    }
};