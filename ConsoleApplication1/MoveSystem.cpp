#include "MoveSystem.h"
#include <iostream>
#include <unordered_set>
void MoveSystem::run(GameState& gs, TurnResult& tr)
{
    //std::uniform_int_distribution<int> move_dist(-4, 4);
    //std::shuffle(gs.entities.begin(), gs.entities.end(), gs.gen);

    //for (auto& entity : gs.entities)
    //{
    //    int xDist = move_dist(gs.gen);
    //    int yDist = move_dist(gs.gen);

    //    int newX = std::clamp(entity.position.x + xDist, 0, gs.map.width - 1);
    //    int newY = std::clamp(entity.position.y + yDist, 0, gs.map.height - 1);

    //    int newIndex = gs.toIndex(newX, newY);

    //    // Handle collision
    //    if (gs.positionIndex[newIndex] != -1)
    //        continue;

    //    GameEvent e;
    //    e.type = EventType::Move;
    //    e.data = MoveEvent{ entity.id, entity.position.x, entity.position.y, newX, newY };

    //    gs.positionIndex[gs.toIndex(entity.position.x, entity.position.y)] = -1;

    //    entity.position.x = newX;
    //    entity.position.y = newY;

    //    gs.positionIndex[newIndex] = entity.id;

    //    tr.events.push_back(e);

    //    std::cout << entity.name << " moved to " << newX << "," << newY << "\n";
    //}
    generateMoveIntents(gs);
    resolveMoveIntents(gs);
    executeMoveIntents(gs,tr);
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
    std::unordered_set<Position, PositionHash> approvedTargets;

    for (auto& entity : gs.entities) {
        MoveIntent& entityIntent = gs.intents[entity.id];
        while (entityIntent.approved == false)
        {
            if (entity.position == entityIntent.target) {
                approvedTargets.insert(entityIntent.target);
                entityIntent.approved = true;
            }
            else if (gs.entityAt(entityIntent.target) == -1 && !approvedTargets.contains(entityIntent.target)) {
                approvedTargets.insert(entityIntent.target);
                entityIntent.approved = true;

            }
            else {
                applyFallback(entity, gs);
            }
        }
    }
};
void MoveSystem::applyFallback(Entity& entity, GameState& gs) {
    int yDist = entity.position.y - gs.intents[entity.id].target.y;
    int xDist = entity.position.x - gs.intents[entity.id].target.x;

    if (yDist != 0) {
        int modifier = yDist / abs(yDist);
        gs.intents[entity.id].target.y += modifier;
    } 
    else if (xDist != 0) {
        int modifier = xDist / abs(xDist);
        gs.intents[entity.id].target.x += modifier;
    }
}

void MoveSystem::executeMoveIntents(GameState& gs, TurnResult& tr) {
    for (auto& intent : gs.intents) {
        Position newPos = intent.second.target;
        Entity& entity = *gs.findById(intent.first);
        GameEvent e;
        e.type = EventType::Move;
        e.data = MoveEvent{ entity.id, entity.position, newPos };


        entity.position = newPos;


        tr.events.push_back(e);

        std::cout << entity.name << " moved to " << newPos.x << "," << newPos.y << "\n";
    }
}
