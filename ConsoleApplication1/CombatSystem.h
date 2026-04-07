#pragma once
#include "GameState.h"
#include "TurnResult.h"
#include "Entity.h"
class CombatSystem
{
	void run(GameState& gs, TurnResult& tr);
	void decideCombats(GameState& gs);
	void runCombat(int attackerID, int defenderID, GameState& gs);
	void attack(int attackerID, int defenderID, GameState& gs);
	void resolveCombat(GameState& gs);
};

