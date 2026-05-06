#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <glm/glm.hpp>
#include "Sprite.h"
#include "Config.h"
#include "AssetsManager.h"

using std::string;
using std::vector;
using std::unordered_map;

class GameClass {
private:
    GameClass() {}
    GameClass(const GameClass&) = delete;
    GameClass &operator=(const GameClass &) = delete;

    string window_title;
    glm::vec2 screen_size;
    SDL_Window* window = nullptr;
    SDL_Renderer *renderer = nullptr;
    AssetsManager *Assets = nullptr;
    TTF_TextEngine *ttf_engine = nullptr;
    double FPS = 0.0f;
    Uint64 FPS_Max = 60;
    Uint64 frame_delay = 0;

    TTF_Font *font = nullptr;
    TTF_Text *text = nullptr;
    SDL_Texture *texture = nullptr;

    MIX_Mixer *Mixer = nullptr;
    MIX_Track *Music = nullptr;

    float x = 320.0f;
    float y = 240.0f;

public:
    ~GameClass() {
        Quit();
    };
    unsigned int Timer = 0;
    static GameClass &GetInstance()
    {
        static GameClass instance;
        return instance;
    }
    void Init(const char *title, short fps_max, int width, int height,
              const char *app_version, const char *app_id);
    void HandleEvents();
    void Update(const double &dt);
    void Render();
    void Quit();

    void RenderTexture(SDL_Texture* texture, const glm::vec2 &position, const glm::vec2 &scale, const float &angle, const SDL_Color &color = {255, 255, 255, 255});
    Uint64 getFrameDelay() const { return frame_delay; }
    Uint64 getFpsMax() const { return FPS_Max; }
};