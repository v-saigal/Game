#pragma once
#include <vector>
#include "GameEvent.h"
struct TurnResult
{
    int turnNumber;
    std::vector<GameEvent> events;
};