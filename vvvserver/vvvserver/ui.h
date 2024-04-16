#pragma once
#include "serv_config.h"
#include<iostream>
#include<random>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;
void setcolor(const char*);
// 定义一个结构体，用于存储ASCII艺术字的信息
struct ASCIIArt {
    std::string text; // 要显示的文本
    int width; // 文本的宽度（字符数）
    int height; // 文本的高度（行数）
    std::vector<std::string> lines; // 文本的每一行
};
ASCIIArt read_ascii_art(const std::string& filename);
// 定义一个函数，用于在控制台上显示ASCII艺术字，并修改背景字符为相同颜色的空格
void show_ascii_art(const ASCIIArt& art, int x, int y, WORD color, std::vector<std::string>& background);

// 定义一个函数，用于生成灰色的字符填充背景，并模拟代码雨下落的效果
void show_rain_background(int width, int height);
void gotoxy(int x, int y);
int codeRain();
int valchat();
void hide();
BOOL SetConsoleColor(WORD wAttributes);
void bgm();