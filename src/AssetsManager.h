#pragma once
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "Config.h"
using std::string;
using std::unordered_map;
class AssetsManager
{
private:
    SDL_Renderer* renderer = nullptr;
    unordered_map<string, SDL_Texture*> textures;
    unordered_map<string, MIX_Audio*> sounds;
    unordered_map<string, TTF_Font*> fonts;
public:
    AssetsManager(SDL_Renderer* renderer);
    ~AssetsManager() = default;
    void Clean();

    // 加载资源
    void LoadTexture(const string& path, const string& id);
    void LoadSound(const string& path, const string& id, bool predecode = true);
    void LoadFont(const string& path, const string& id, const float &size);
    // 获取资源，如果没有找到则加载一个空资源并返回
    SDL_Texture* GetTexture(const string& id);
    MIX_Audio* GetSound(const string& id);
    TTF_Font* GetFont(const string &id);
};  