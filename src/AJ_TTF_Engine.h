#pragma once
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

using std::string;
using std::vector;

class AJ_TTF_Object
{
private:
    string name;
    string text;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_FRect rect;
    SDL_Color color;
public:
    AJ_TTF_Object(string name, string text, SDL_Color color, TTF_Font* font);

    ~AJ_TTF_Object();

    void Render(SDL_Renderer* renderer);   
    
};

class AJ_TTF_Engine {
private:
    vector<AJ_TTF_Object*> objects;
public:
    AJ_TTF_Engine(TTF_Font* font);
    ~AJ_TTF_Engine() = default;

    TTF_TextEngine* CreateTextEngine();
    void DestroyTextEngine(TTF_TextEngine* engine);

    AJ_TTF_Object* CreateTextObject(string name, string text, SDL_Color color);
    void DestroyTextObject(const string &name);
};