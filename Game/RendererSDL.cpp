#include "RendererSDL.h"
#include <SDL3/SDL.h>

RendererSDL::RendererSDL()
    : m_renderer(nullptr)
{
}

RendererSDL::~RendererSDL()
{
    Shutdown();
}

bool RendererSDL::Initialize(SDL_Renderer* renderer)
{
    if (!renderer) return false;
    m_renderer = renderer;
    return true;
}

void RendererSDL::BeginFrame()
{
    // no-op, Begin/End handled explicitly
}

void RendererSDL::Clear()
{
    if (!m_renderer) return;
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void RendererSDL::Draw(SDL_Texture* tex, const SDL_FRect* dst)
{
    if (!m_renderer || !tex) return;
    SDL_RenderTexture(m_renderer, tex, NULL, dst);
}

void RendererSDL::Present()
{
    if (!m_renderer) return;
    SDL_RenderPresent(m_renderer);
}

void RendererSDL::Shutdown()
{
    // renderer lifetime managed externally when created with CreateWindowAndRenderer
    m_renderer = nullptr;
}
