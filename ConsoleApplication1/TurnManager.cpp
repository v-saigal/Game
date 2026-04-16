#include "TurnManager.h"
#include <iostream>
TurnResult TurnManager::simulateTurn(GameState& gs) {
	TurnResult tr;
	tr.turnNumber = gs.turnNumber;
	movement.run(gs, tr);
	combat.run(gs, tr);
	cleanupTurn(gs);
	if (gs.entities.size() < 2) {
		std::cout << "Game over!";
		std::cin;
	}
	return tr;
}
void TurnManager::cleanupTurn(GameState& gs) {
	gs.entities.erase(
		std::remove_if(gs.entities.begin(), gs.entities.end(),
			[](const Entity& e) {
				return e.alive == false;
			}),
		gs.entities.end()
	);
	gs.combatants.clear();
	gs.intents.clear();
	for (auto& Entity : gs.entities) {
		Entity.engagedInCombat = false;
		
	}
}
