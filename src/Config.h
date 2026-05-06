// 配置文件
#pragma once
#ifndef SDL3_UNDERTALE_ENGINE_CONFIG_H
#define SDL3_UNDERTALE_ENGINE_CONFIG_H

#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

struct Font_Size_and_Path {
    int size;
    string path;
};

#define MAX_SPRITES 1000000000 // 最大的精灵数量
#define MAX_LAYERS 1000000000 // 最大的层数量

#define GAME_TITLE "SDL3 UNDERTALE ENGINE 中文测试" // 游戏标题
#define GAME_VERSION "0.0.1" // 游戏版本
#define GAME_APP_ID "com.angeljerry.undertale-engine" // 游戏应用ID
#define GAME_FPS 60 // 游戏帧率
#define GAME_WIDTH 640 // 游戏窗口宽度
#define GAME_HEIGHT 480 // 游戏窗口高度

// AssetsManager 会自动加载以下资源
const unordered_map<string, string> Assets_Textures = {
    {"soul", "assets/textures/soul.png"}
};
const unordered_map<string, string> Assets_Sounds = {
    {"empty", "assets/sounds/empty.wav"}
};


const unordered_map<string, Font_Size_and_Path> Assets_Fonts = {
    {"FZXS12", {24, "assets/fonts/FZXS12.ttf"}}
};













#endif //SDL3_UNDERTALE_ENGINE_CONFIG_H