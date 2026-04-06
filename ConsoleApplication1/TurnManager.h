#pragma once
#include "GameState.h"
#include "MoveSystem.h"
#include "CombatSystem.h"

class TurnManager
{
public:
    TurnResult simulateTurn(GameState& state);

private:
    MoveSystem movement;
    CombatSystem combat;
};


