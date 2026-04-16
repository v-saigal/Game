#pragma once
#include "Position.h"
#include <cstdlib>

inline bool isAdjacent(const Position& a, const Position& b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) == 1;
}

