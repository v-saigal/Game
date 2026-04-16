#pragma once
#include "GameState.h"
#include "TurnResult.h"
#include "Entity.h"
#include "GridUtils.h"
class CombatSystem
{
	public:
		void run(GameState& gs, TurnResult& tr);
		void decideCombats(GameState& gs);
		void runCombat(GameState& gs, TurnResult& tr);
		void attack(Entity& attacker, Entity& defender, GameState& gs, TurnResult& tr);
		void resolveCombat(GameState& gs);
};

