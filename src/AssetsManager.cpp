#include "AssetsManager.h"

AssetsManager::AssetsManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;    
    SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);
    for (auto& texture : Assets_Textures)
        LoadTexture(texture.second, texture.first);
    for (auto& sound : Assets_Sounds)
        LoadSound(sound.second, sound.first);
    // for (auto& font : Assets_Fonts)
    //     LoadFont(font.second.path, font.first, font.second.size);
    LoadFont("assets/fonts/FZXS12.ttf", "FZXS12", 24);
}
void AssetsManager::Clean()
{
    for (auto& texture : textures)
        SDL_DestroyTexture(texture.second);
    textures.clear();
    for (auto& sound : sounds)
        MIX_DestroyAudio(sound.second);
    sounds.clear();
    for (auto& font : fonts)
        TTF_CloseFont(font.second);
    fonts.clear();
}
void AssetsManager::LoadTexture(const string& path, const string& id)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s.\n", SDL_GetError());
        return;
    }
    textures.emplace(id, texture);
    return;
}
void AssetsManager::LoadSound(const string& path, const string& id, bool predecode)
{

    MIX_Audio* sound = MIX_LoadAudio(NULL, path.c_str(), predecode);
    if (!sound)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s.\n", SDL_GetError());
        return;
    }
    sounds.emplace(id, sound);
    return;
}

void AssetsManager::LoadFont(const string& path, const string& id, const float& size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                     "Failed to load font: %s.\n", SDL_GetError());
        return;
    }
    fonts.emplace(id, font);
    return;
}

SDL_Texture* AssetsManager::GetTexture(const string& id)
{
    auto it = textures.find(id);
    if (it == textures.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Failed to get texture: %s.\n", id.c_str());
        return nullptr;
    }
    return it->second;
}
MIX_Audio* AssetsManager::GetSound(const string& id)
{
    auto it = sounds.find(id);
    if (it == sounds.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Failed to get sound: %s.\n", id.c_str());
        return nullptr;
    }
    return it->second;
}
TTF_Font* AssetsManager::GetFont(const string &id)
{
    auto it = fonts.find(id);
    if (it == fonts.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
                     "Failed to get font: %s.\n", id.c_str());
        return nullptr;
    }
    return it->second;
}
