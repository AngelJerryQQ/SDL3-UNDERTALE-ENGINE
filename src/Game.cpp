#include "Game.h"
#include <SDL3/SDL_oldnames.h>

void GameClass::Init(const char* title, short fps_max, int width, int height, const char* app_version,
                     const char* app_id)
{
    SDL_SetAppMetadata(title, app_version, app_id);
    FPS_Max = fps_max;
    frame_delay = 1000000000 / fps_max;
    window = NULL;
    renderer = NULL;
    ttf_engine = NULL;

    window_title = string(title);
    screen_size = glm::vec2(width, height);

    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL initialization failed: %s\n", SDL_GetError());
    }

    if (!MIX_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }

    // Mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    // if (!Mixer){
    //     SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer创建失败: %s\n", SDL_GetError());
    // }


    // Mix_AllocateChannels(16);
    // Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    // Mix_Volume(-1, MIX_MAX_VOLUME / 4);

    if (!TTF_Init())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF initialization failed: %s\n", SDL_GetError());
    }
    SDL_CreateWindowAndRenderer(title, width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (!window || !renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create a window or renderer: %s\n", SDL_GetError());
    }

    // 初始化AssetsManager
    Assets = new AssetsManager(renderer);

    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 设置默认的纹理缩放模式
    SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);

    ttf_engine = TTF_CreateRendererTextEngine(renderer);
    font = TTF_OpenFont("assets/fonts/FZXS12.ttf", 24);

    text = TTF_CreateText(ttf_engine, font, "文本引擎: SDL3 UNDERTALE ENGINE! ", 0);
    // 设置文本属性
    TTF_SetTextColor(text, 255, 255, 255, 255);
    // TTF_SetTextWrapWidth(text, 50);

    texture = Assets->GetTexture("soul");

    return;
}
void GameClass::Quit()
{
    if (Assets)
    {
        Assets->Clean();
        delete Assets;
        Assets = nullptr;
    }

    if (ttf_engine)
    {
        TTF_DestroyRendererTextEngine(ttf_engine);
        ttf_engine = NULL;
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    return;
}
void GameClass::Update(const double& dt) {

    Timer++;
    FPS = 1.0f / dt;

    auto currentKeyStates = SDL_GetKeyboardState(NULL);
    double speed = 3;
    if (currentKeyStates[SDL_SCANCODE_X]){
        speed = 1.5f;
    }
    if (currentKeyStates[SDL_SCANCODE_UP]){
        y += -speed;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN]){
        y += speed;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT]){
        x += -speed;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT]){
        x += speed;
    }


    return;
}
void GameClass::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // 在渲染循环中直接绘制文本
    TTF_DrawRendererText(text, 100, 200);

    // 创建文本纹理
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "文本纹理: SDL3 UNDERTALE ENGINE! ", 0, color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    // 渲染文本
    SDL_FRect textRect = {100, 300, static_cast<float>(surface->w), static_cast<float>(surface->h)};
    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const string fps_text = std::to_string(FPS);
    const string x_text = std::to_string(x);
    const string y_text = std::to_string(y);
    SDL_RenderDebugText(renderer, 10, 10, fps_text.c_str());
    SDL_RenderDebugText(renderer, 10, 30, x_text.c_str());
    SDL_RenderDebugText(renderer, 10, 50, y_text.c_str());

    // 绘制纹理
    RenderTexture(texture, glm::vec2(x, y), glm::vec2(16, 16), (Timer * 2 % 360), {255, 255, 255, 255});

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return;
}

/**
 * 渲染带有旋转、缩放和颜色调节的纹理
 * 
 * @param texture 要绘制的纹理
 * @param position 纹理的位置
 * @param scale 纹理的大小
 * @param angle 纹理的旋转角度
 * @param color 纹理的颜色
 */
void GameClass::RenderTexture(SDL_Texture* texture, const glm::vec2 &position, const glm::vec2 &scale, const float &angle, const SDL_Color &color) {
    // 1. 纹理尺寸的一半
    const float texW_half = texture->w / 2.0f;
    const float texH_half = texture->h / 2.0f;

    // 2. 缩放后矩形
    const SDL_FRect dst_rect = {
    position.x - texW_half, 
    position.y - texH_half,      
    scale.x, 
    scale.y
};

    // 3. 颜色 & 透明度
    SDL_SetTextureColorModFloat(texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture, color.a);
    // 4. 旋转中心点
    const SDL_FPoint center = {(float)texW_half, (float)texH_half};

    // 5. 绘制
    SDL_RenderTextureRotated(renderer, texture, NULL, &dst_rect, angle, &center, SDL_FLIP_NONE);
}