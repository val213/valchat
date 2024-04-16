//ui.cpp
#include"ui.h"
void setcolor(const char* c)
{
    system(c);

}
// �����Ҫ��ͷ�ļ�
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼������
void hide() { //����һ�����ع��ĺ���
    CONSOLE_CURSOR_INFO cursor; //����һ�������Ϣ�ṹ��
    cursor.bVisible = 0; //���ù�겻�ɼ�
    cursor.dwSize = 1; //���ù���СΪ1
    SetConsoleCursorInfo(han, &cursor); //���ÿ���̨�����Ϣ
}


// ����һ�����������ڴ��ļ��ж�ȡASCII������
ASCIIArt read_ascii_art(const std::string& filename) {
    ASCIIArt art;
    std::ifstream file(filename); // ���ļ�
    if (file.is_open()) { // ����ļ��򿪳ɹ�
        std::getline(file, art.text); // ��ȡ��һ�У���Ϊ�ı�
        art.width = 0; // ��ʼ�����Ϊ0
        art.height = 0; // ��ʼ���߶�Ϊ0
        std::string line; // ���ڴ洢ÿһ�е�����
        while (std::getline(file, line)) { // ѭ����ȡÿһ�У�ֱ���ļ�����
            art.lines.push_back(line); // ��ÿһ����ӵ�lines������
            art.height++; // �߶ȼ�1
            if (line.size() > art.width) { // �����ǰ�еĳ��ȴ��ڿ��
                art.width = line.size(); // ���¿��Ϊ��ǰ�еĳ���
            }
        }
        file.close(); // �ر��ļ�
    }
    return art; // ����ASCII�����ֽṹ��
}

// ����һ�������������ڿ���̨����ʾASCII�����֣����޸ı����ַ�Ϊ��ͬ��ɫ�Ŀո�
void show_ascii_art(const ASCIIArt& art, int x, int y, WORD color, std::vector<std::string>& background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    COORD coord; // ����һ������ṹ�壬�������ù��λ��
    coord.X = x; // ���ú�����Ϊx
    coord.Y = y; // ����������Ϊy
    SetConsoleCursorPosition(hConsole, coord); // ���ù��λ��
    for (int i = 0; i < art.height; i++) { // ѭ������ÿһ��
        SetConsoleTextAttribute(hConsole, color); // �����ı���ɫΪcolor
        std::cout << art.lines[i] << std::endl; // �����ǰ�У�������
        for (int j = 0; j < art.width; j++) { // ѭ������ÿһ��
            if (art.lines[i][j] != ' ') { // �����ǰλ�ò��ǿո�˵����ASCII�����ֵ�һ����
                background[y + i][x + j] = ' '; // �������ַ��滻Ϊ�ո�
            }
        }
        coord.Y++; // �������1
        SetConsoleCursorPosition(hConsole, coord); // ���ù��λ��
    }
}

// ����һ���������������ɻ�ɫ���ַ���䱳������ģ������������Ч��
void show_rain_background(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ����̨���
    COORD coord; // ����һ������ṹ�壬�������ù��λ��
    coord.X = 0; // ���ú�����Ϊ0
    coord.Y = 0; // ����������Ϊ0
    SetConsoleOutputCP(65001);
    char val[] = "�ڿ��";
    std::vector<std::string> background(height); // ����һ���ַ������������ڴ洢������ÿһ��

    srand(time(NULL)); // �������������

    for (int i = 0; i < height; i++) { // ѭ������ÿһ��
        for (int j = 0; j < width; j++) { // ѭ������ÿһ��
            // �������һ��ASCII����0��3֮����ַ�����Ϊ���������
            // ���ַ���ӵ���ǰ�е��ַ�����
            background[i].push_back('#');
        }
    }

    // ����һ���������������ڴ洢ÿһ�еĴ�����ĳ���
    std::vector<int> rain_length(width);
    // ����һ���������������ڴ洢ÿһ�еĴ�����ĵ�ǰλ��
    std::vector<int> rain_position(width);

    for (int j = 0; j < width; j++)
    { // ѭ������ÿһ��

        // �������һ��������ĳ��ȣ���Χ��2��5֮��
        rain_length[j] = 1;
        // �������һ��������ĵ�ǰλ�ã���Χ��0��height֮��
        rain_position[j] = j;
    }
    int t = 15;
    while (t--) { // ����ѭ����ģ������겻�������Ч��
        Sleep(100);
        for (int i = 0; i < height; i++) { // ѭ������ÿһ��
            SetConsoleCursorPosition(hConsole, coord); // ���ù��λ��

            for (int j = 0; j < width; j++) { // ѭ������ÿһ��
                if (i >= rain_position[j] && i < rain_position[j] + rain_length[j]) {
                    // �����ǰλ���ڴ�����ķ�Χ�ڣ��������ı���ɫΪ��ɫ
                    background[i][j] = '.';
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                }
                else {
                    // ���򣬾������ı���ɫΪ��ɫ
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                // �����ǰλ�õ��ַ�

                std::cout << background[i][j];
            }
            std::cout << std::endl; // ����
            coord.Y++; // �������1
        }
        coord.Y = 0; // ����������Ϊ0

        for (int j = 0; j < width; j++) { // ѭ������ÿһ��
            // ���´�����ĵ�ǰλ�ã���������˸߶ȣ�������Ϊ0
            rain_position[j] = (rain_position[j] + 1) % height;
        }

        Sleep(100); // �ӳ�100���룬ģ�⶯��Ч��
    }
}

// ���������������ڲ�����������
int codeRain() {
    ASCIIArt art = read_ascii_art("ascii_art.txt"); // ���ļ��ж�ȡASCII������

    int width = 74; // �������̨�Ŀ�ȣ��ַ�����
    int height = 7; // �������̨�ĸ߶ȣ�������

    std::vector<std::string> background(height); // ����һ���ַ������������ڴ洢������ÿһ��

    show_rain_background(width, height); // �ڿ���̨����ʾ��ɫ���ַ���䱳������ģ������������Ч��

    int x = (width - art.width) / 2; // ����ASCII�����ֵĺ����꣬ʹ�������ʾ
    int y = (height - art.height) / 2; // ����ASCII�����ֵ������꣬ʹ�������ʾ

    show_ascii_art(art, x, y, FOREGROUND_GREEN, background); // �ڿ���̨����ʾASCII�����֣����޸ı����ַ�Ϊ��ͬ��ɫ�Ŀո�
    return 0; // ����0����ʾ������������
}
int valchat()
{
    Sleep(4000);
    gotoxy(0, 0);
    PlaySound(TEXT("C:\\Users\\yangluwei\\source\\repos\\valclient\\valclient\\��ȷ-ϵͳ��ʾ��Ϸ��ʾ_������_aigei_com.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout <<
        "oooooo     oooo           oooo    .oooooo.   oooo                      .   \n" <<
        " `888.     .8'            `888   d8P'  `Y8b  `888                    .o8   \n" <<
        "  `888.   .8'    .oooo.    888  888           888 .oo.    .oooo.   .o888oo \n" <<
        "   `888. .8'    `P  )88b   888  888           888P\"Y88b  `P  )88b    888   \n" <<
        "    `888.8'      .oP\"888   888  888           888   888   .oP\"888    888   \n" <<
        "     `888'      d8(  888   888  `88b    ooo   888   888  d8(  888    888 . \n" <<
        "      `8'       `Y888\"\"8o o888o  `Y8bood8P'  o888o o888o `Y888\"\"8o   \"888	\n";


    return 0;


}


void gotoxy(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
BOOL SetConsoleColor(WORD wAttributes)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
        return FALSE;

    return SetConsoleTextAttribute(hConsole, wAttributes);
}
void bgm()
{
    Sleep(5500);
    PlaySound(TEXT("D:\\����\\ewsfm-yslvo .wav"), NULL, SND_FILENAME | SND_ASYNC);;
}