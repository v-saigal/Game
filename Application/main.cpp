#include "LConst.h"
#include "LTimer.h"
#include "LUtil.h"
#include "TileMap.h"
#include "GameState.h"
#include "Entity.h"
#include "Map.h"
#include "Sprite.h"
#include "LRenderer.h"
#include "TurnResult.h"
#include "TurnManager.h"
#include "Position.h"
int main(int argc, char* args[])
{
    // --- Initialize GameState ---
    std::string names[6] = { "Asterie", "Khalmariat", "Benzaiten", "Abe", "Maff", "Luminea" };
    int entIDs[6] = { 0, 1, 2, 3, 4, 5 };
    int xLocs[6] = { 1, 12, 34, 17, 42, 28 };
    int yLocs[6] = { 1, 3, 7, 12, 5, 14 };

    GameState gs(48, 16);
    
    for (int i = 0; i < 6; i++)
    {
        Position pos{xLocs[i], yLocs[i]};
        gs.entities.push_back(Entity(names[i], xLocs[i], yLocs[i], entIDs[i]));
    }

   

    // --- Initialize SDL ---
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!initSDL(&window, &renderer, kScreenWidth, kScreenHeight, "Battle Royale Simulation"))
        return 1;

    // --- Initialize Renderer ---
    LRenderer gameRenderer(renderer);
    gameRenderer.initialiseSprites(gs);

    // --- Main game loop ---
    bool quit = false;
    LTimer frameTimer;
    //Simulate first turn of logic ---
   TurnManager tm;
   TurnResult result = tm.simulateTurn(gs);
   // Process game events (movement, combat, etc.)
   gameRenderer.processEvents(result);
   gameRenderer.rs = RenderState::PlayingEvents;
    while (!quit)
    {
        frameTimer.start();

        // Handle window events
        gameRenderer.handleEvents(quit);



        // Calculate delta time in seconds
        float deltaTime = static_cast<float>(frameTimer.getDeltaSeconds()) / 1'000'000'000.0f;

        // Render frame with delta time
        gameRenderer.renderFrame(gs, deltaTime);
    }

    // --- Cleanup ---
    closeSDL(window, renderer);

    return 0;
}
