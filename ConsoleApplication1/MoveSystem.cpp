#include "MoveSystem.h"
#include <iostream>
void MoveSystem::run(GameState& gs, TurnResult& tr)
{
    std::uniform_int_distribution<int> move_dist(-4, 4);
    std::shuffle(gs.entities.begin(), gs.entities.end(), gs.gen);

    for (auto& entity : gs.entities)
    {
        int xDist = move_dist(gs.gen);
        int yDist = move_dist(gs.gen);

        int newX = std::clamp(entity.position.x + xDist, 0, gs.map.width - 1);
        int newY = std::clamp(entity.position.y + yDist, 0, gs.map.height - 1);

        int newIndex = gs.toIndex(newX, newY);

        // Handle collision
        if (gs.positionIndex[newIndex] != -1)
            continue;

        GameEvent e;
        e.type = EventType::Move;
        e.data = MoveEvent{ entity.id, entity.position.x, entity.position.y, newX, newY };

        gs.positionIndex[gs.toIndex(entity.position.x, entity.position.y)] = -1;

        entity.position.x = newX;
        entity.position.y = newY;

        gs.positionIndex[newIndex] = entity.id;

        tr.events.push_back(e);

        std::cout << entity.name << " moved to " << newX << "," << newY << "\n";
    }
};
void MoveSystem::generateMoveIntents(GameState& gs)
{
    gs.intents.clear();

    std::uniform_int_distribution<int> move_dist(-4, 4);
    std::shuffle(gs.entities.begin(), gs.entities.end(), gs.gen);

    for (auto& entity : gs.entities)
    {
        int xDist = move_dist(gs.gen);
        int yDist = move_dist(gs.gen);

        int newX = std::clamp(entity.position.x + xDist, 0, gs.map.width - 1);
        int newY = std::clamp(entity.position.y + yDist, 0, gs.map.height - 1);

        MoveIntent intent;
        intent.target = Position{ newX, newY };
        intent.hasIntent = true;

        gs.intents[entity.id] = intent;
    }
}
void MoveSystem::resolveMoveIntents(GameState& gs)
{
    
};


