#pragma once
#include "serv_config.h"
#include<iostream>
#include<random>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;
void setcolor(const char*);
// ����һ���ṹ�壬���ڴ洢ASCII�����ֵ���Ϣ
struct ASCIIArt {
    std::string text; // Ҫ��ʾ���ı�
    int width; // �ı��Ŀ�ȣ��ַ�����
    int height; // �ı��ĸ߶ȣ�������
    std::vector<std::string> lines; // �ı���ÿһ��
};
ASCIIArt read_ascii_art(const std::string& filename);
// ����һ�������������ڿ���̨����ʾASCII�����֣����޸ı����ַ�Ϊ��ͬ��ɫ�Ŀո�
void show_ascii_art(const ASCIIArt& art, int x, int y, WORD color, std::vector<std::string>& background);

// ����һ���������������ɻ�ɫ���ַ���䱳������ģ������������Ч��
void show_rain_background(int width, int height);
void gotoxy(int x, int y);
int codeRain();
int valchat();
void hide();
BOOL SetConsoleColor(WORD wAttributes);
void bgm();