#pragma once

#include <vector>
#include "EntityIntent.h"
#include "Entity.h"
#include "Map.h"
#include <random>
#include <unordered_map>
#include "Position.h"
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
    int toIndex(Position pos) const
    {
        return pos.y * map.width + pos.x;
    }

    // Safe accessors
    int entityAt(Position pos) const
    {
        return positionIndex[toIndex(pos)];
    }

    void setEntity(Position pos, int id)
    {
        positionIndex[toIndex(pos)] = id;
    }

    void clearTile(Position pos)
    {
        positionIndex[toIndex(pos)] = EMPTY_TILE;
    }
};