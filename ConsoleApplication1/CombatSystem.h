#pragma once
#include "GameState.h"
#include "TurnResult.h"
class CombatSystem
{
	void run(GameState& gs, TurnResult& tr);
	void resolveCombat();
};

