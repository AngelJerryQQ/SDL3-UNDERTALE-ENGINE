#include <SDL3/SDL_oldnames.h>
#include "src/Game.h"

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include <direct.h>


static auto &Game = GameClass::GetInstance();

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    char* current_cwd = _getcwd(nullptr, 0);
    printf("Current working directory: %s\n", current_cwd);
    Game.Init(GAME_TITLE, GAME_FPS, GAME_WIDTH, GAME_HEIGHT, GAME_VERSION, GAME_APP_ID);
    SDL_Log("已完成Game类配置！\n");
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
        if (event->key.repeat == SDLK_ESCAPE)
        {
            return SDL_APP_SUCCESS;
        }
        break;
    }
    return SDL_APP_CONTINUE;
}
namespace Ticks
{
    double dt = 0.0;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    auto start = SDL_GetTicksNS();
    const auto frame_delay_ = Game.GetInstance().getFrameDelay();
    Game.Update(Ticks::dt);
    Game.Render();
    auto end = SDL_GetTicksNS();
    auto elapsed = end - start;
    if (elapsed < frame_delay_)
    {
        SDL_DelayNS(frame_delay_ - elapsed);
        Ticks::dt = frame_delay_ / 1.0e9;
    }
    else
        Ticks::dt = elapsed / 1.0e9;
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    Game.Quit();
    return;
}
