#include "TurnManager.h"

TurnResult TurnManager::simulateTurn(GameState& gs) {
	TurnResult tr;
	tr.turnNumber = gs.turnNumber;
	movement.run(gs, tr);
	return tr;
}
