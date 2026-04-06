#include "LRenderer.h"
#include "LConst.h"
#include "GameEvent.h"
#include <SDL3/SDL.h>

LRenderer::LRenderer(SDL_Renderer* renderer)
    : mRenderer(renderer), mMapTexture(mRenderer), mTileMap(mMapTexture), mSpriteTexture(mRenderer)
{
    loadMedia(mMapTexture, "TileMapSheet.png");
    loadMedia(mSpriteTexture, "Sprite.png");
}

void LRenderer::loadMedia(LTexture& texture, const std::string& path) {
    if (!texture.loadFromFile(path))
        SDL_Log("Failed to load %s: %s", path.c_str(), SDL_GetError());
}

void LRenderer::initialiseSprites(const GameState& gs) {
    sprites.clear();
    for (const auto& entity : gs.entities) {
        auto sprite = std::make_unique<Sprite>(mSpriteTexture);
        sprite->setPos(entity.position.x * kTileMapWidth, entity.position.y * kTileMapHeight);
        sprites.emplace(entity.id, std::move(sprite));
    }
}

void LRenderer::handleEvent(const GameEvent& e) {
    if (std::holds_alternative<MoveEvent>(e.data)) {
        auto move = std::get<MoveEvent>(e.data);
        auto it = sprites.find(move.entityID);
        if (it != sprites.end()) {
            float x = move.toX * kTileMapWidth;
            float y = move.toY * kTileMapHeight;
            it->second->moveTo(x, y);
        }
    }
}
void LRenderer::startEvent(const GameEvent& e) {
    if (std::holds_alternative<MoveEvent>(e.data)) {
        auto move = std::get<MoveEvent>(e.data);
        auto it = sprites.find(move.entityID);
        if (it != sprites.end()) {
            float x = move.toX * kTileMapWidth;
            float y = move.toY * kTileMapHeight;
            it->second->moveTo(x, y);
        }
    }
}

void LRenderer::processEvents(const TurnResult& result) {
    for (const auto& e : result.events)
        eventQueue.push_back(e);
        
}

void LRenderer::renderFrame(const GameState& gs, float deltaTime)
{
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer);

    // --- Render map ---
    for (size_t y = 0; y < gs.map.grid.size(); ++y)
        for (size_t x = 0; x < gs.map.grid[y].size(); ++x)
            mTileMap.render((int)x, (int)y, gs.map.grid[y][x].lType);

    // --- Update & render sprites, and check movement in one loop ---
    bool anyMoving = false;
    for (auto& [id, sprite] : sprites)
    {
        sprite->update(deltaTime);
        sprite->render();
        if (sprite->isMoving())
            anyMoving = true;
    }

    // --- Event queue / state management ---
    if (rs == RenderState::PlayingEvents)
    {
        if (!anyMoving)
        {
            if (!eventQueue.empty())
            {
                startEvent(eventQueue.front());  // start next event
                eventQueue.pop_front();
            }
            else
            {
                rs = RenderState::WaitingForPlayer;  // turn finished
            }
        }
    }

    SDL_RenderPresent(mRenderer);
}

void LRenderer::handleEvents(bool& quit) {
    SDL_Event e;
    SDL_zero(e);
    while (SDL_PollEvent(&e))
        if (e.type == SDL_EVENT_QUIT) quit = true;
}
