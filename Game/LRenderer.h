#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <memory>
#include "Map.h"
#include "TileMap.h"
#include "LTexture.h"
#include "Sprite.h"
#include "TurnResult.h"
#include "GameState.h"
#include "RenderState.h"
#include <deque>

class LRenderer
{
public:
    LRenderer(SDL_Renderer* renderer);

    void loadMedia(LTexture& texture, const std::string& path);
    std::deque<GameEvent> eventQueue;
    RenderState rs;
    void initialiseSprites(const GameState& gs);
    void processEvents(const TurnResult& result);
    void handleEvent(const GameEvent& e);
    void startEvent(const GameEvent& e);

    void renderFrame(const GameState& gs, float deltaTime);
    void handleEvents(bool& quit);

private:
    SDL_Renderer* mRenderer;
    LTexture mMapTexture;
    LTexture mSpriteTexture;
    TileMap mTileMap;

    std::unordered_map<int, std::unique_ptr<Sprite>> sprites;
};
