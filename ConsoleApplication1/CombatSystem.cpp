#include "CombatSystem.h"
#include <iostream>


void CombatSystem::run(GameState& gs, TurnResult& tr) {
	decideCombats(gs);
	runCombat(gs, tr);
}
void CombatSystem::decideCombats(GameState& gs) {
	for (auto& entity : gs.entities) {

		if (entity.engagedInCombat) {
			continue;
		}

		Position up{ entity.position.x, entity.position.y - 1 };
		Position down{ entity.position.x, entity.position.y + 1 };
		Position left{ entity.position.x - 1, entity.position.y };
		Position right{ entity.position.x + 1, entity.position.y };
		Position neighbours[4] = { up, down, left, right };

		for (auto& neighbour : neighbours) {
			if (gs.map.posInBounds(neighbour)) {
				int neighbourId = gs.entityAt(neighbour);
				if (neighbourId == -1) {
					continue;
				}
				Entity& nEnt = *gs.findById(neighbourId);

				if (!nEnt.engagedInCombat) {
					gs.combatants.push_back(std::pair<int, int>(entity.id, nEnt.id));
					entity.engagedInCombat = true;
					nEnt.engagedInCombat = true;
					break;
				}
			}
		}
	}
}
	

void CombatSystem::runCombat(GameState& gs, TurnResult& tr) {
	
	for (auto& combatants : gs.combatants) {
		
		Entity& attacker = *gs.findById(combatants.first);
		Entity& defender = *gs.findById(combatants.second);

		GameEvent e;
		e.type = EventType::Attack;
		e.data = AttackEvent{ combatants.first, combatants.second };
		//tr.events.push_back(e);
		std::cout << attacker.name << " attacked " << defender.name << "\n";
		attack(attacker, defender, gs, tr);
		if (defender.health < 1) {
			defender.alive = false;
			gs.clearTile(defender.position);
			std::cout << defender.name << " has perished.\n";
			continue;
		}
		GameEvent e2;
		e2.type = EventType::Attack;
		e2.data = AttackEvent{ combatants.first, combatants.second };
		std::cout << defender.name << " retaliated against " << attacker.name << "\n";
		attack(defender, attacker, gs, tr);
		if (attacker.health < 1) {
			attacker.alive = false;
			gs.clearTile(attacker.position);
			std::cout << attacker.name << " has perished.\n";
			continue;
		}
		//tr.events.push_back(e2);
	}


}
void CombatSystem::attack(Entity& attacker, Entity& defender, GameState& gs, TurnResult& tr) {
	std::uniform_int_distribution<int> damage(1, 3);
	int dmg = damage(gs.gen);
	defender.health -= dmg;
	GameEvent e;
	e.type = EventType::Damage;
	e.data = DamageEvent{ defender.id, dmg };
	//tr.events.push_back(e);
	std::cout << defender.name << " took " << std::to_string(dmg) << " damage. " << std::to_string(defender.health) << " remaining.\n";
}
void CombatSystem::resolveCombat(GameState& gs) {
	gs.entities.erase(
		std::remove_if(gs.entities.begin(), gs.entities.end(),
			[](const Entity& e) {
				return e.health <= 0;
			}),
		gs.entities.end()
	);
}