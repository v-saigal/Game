#include "pch.h"
#include "GameState.h"
#include "Entity.h"
#include "Map.h"
#include "MoveSystem.h"
#include "TurnResult.h"
#include "TurnManager.h"
#include "Position.h"
#include "EntityIntent.h"
#include <unordered_map>
// --- Initialize GameState ---
std::string names[6] = { "Asterie", "Khalmariat", "Benzaiten", "Abe", "Maff", "Luminea" };
int entIDs[6] = { 0, 1, 2, 3, 4, 5 };
int xLocs[6] = { 1, 1, 1, 2, 2, 2 };
int yLocs[6] = { 1, 2, 3, 1, 2, 3 };

GameState gs(48, 16);

TEST(TestCaseName, TestName) {

    for (int i = 0; i < 6; i++)
    {
        Position pos{ xLocs[i], yLocs[i] };
        gs.positionIndex[gs.toIndex(pos)] = entIDs[i];
        gs.entities.push_back(Entity(names[i], pos, entIDs[i]));
        
    }
    Position newPos{ 2 ,2 };
    MoveIntent intent{ newPos, 0, true };
    gs.intents[0] = intent;
    MoveSystem ms;
    TurnResult tr;
    tr.turnNumber = gs.turnNumber;
    ms.executeMoveIntents(gs, tr);
    EXPECT_EQ(1, 1);
}