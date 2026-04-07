#pragma once
#include "GameState.h"
#include "TurnResult.h"
class MoveSystem
{
	public:
		void run(GameState& gs, TurnResult& tr);
		void generateMoveIntents(GameState& gs);
		void resolveMoveIntents(GameState& gs);
		void applyFallback(Entity& entity, GameState& gs);
		void executeMoveIntents(GameState& gs, TurnResult& tr);

	private:
	

};
