#include "TextureManager.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* renderer)
    : m_renderer(renderer)
{
}

TextureManager::~TextureManager()
{
    Shutdown();
}

SDL_Texture* TextureManager::Load(const std::string& path)  
{
    auto it = m_cache.find(path);
    if (it != m_cache.end()) return it->second;

    SDL_Surface* surf = SDL_LoadPNG(path.c_str());
    if (!surf) {
        SDL_Log("IMG_Load failed for %s", path.c_str());
        return nullptr;
    }   

    SDL_Texture* tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    SDL_DestroySurface(surf);
    if (!tex) {
        SDL_Log("SDL_CreateTextureFromSurface failed for %s", path.c_str());
        return nullptr;
    }

    m_cache.emplace(path, tex);
    return tex;
}

SDL_Texture* TextureManager::Get(const std::string& path) const
{
    auto it = m_cache.find(path);
    return (it != m_cache.end()) ? it->second : nullptr;
}

void TextureManager::Unload(const std::string& path)
{
    auto it = m_cache.find(path);
    if (it == m_cache.end()) return;
    SDL_DestroyTexture(it->second);
    m_cache.erase(it);
}

void TextureManager::Shutdown()
{
    for (auto &p : m_cache) SDL_DestroyTexture(p.second);
    m_cache.clear();
}
