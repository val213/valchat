//ui.cpp
#include"ui.h"
void setcolor(const char* c)
{
    system(c);

}
// 引入必要的头文件
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE); //获取标准输出句柄
void hide() { //定义一个隐藏光标的函数
    CONSOLE_CURSOR_INFO cursor; //定义一个光标信息结构体
    cursor.bVisible = 0; //设置光标不可见
    cursor.dwSize = 1; //设置光标大小为1
    SetConsoleCursorInfo(han, &cursor); //设置控制台光标信息
}


// 定义一个函数，用于从文件中读取ASCII艺术字
ASCIIArt read_ascii_art(const std::string& filename) {
    ASCIIArt art;
    std::ifstream file(filename); // 打开文件
    if (file.is_open()) { // 如果文件打开成功
        std::getline(file, art.text); // 读取第一行，作为文本
        art.width = 0; // 初始化宽度为0
        art.height = 0; // 初始化高度为0
        std::string line; // 用于存储每一行的内容
        while (std::getline(file, line)) { // 循环读取每一行，直到文件结束
            art.lines.push_back(line); // 将每一行添加到lines向量中
            art.height++; // 高度加1
            if (line.size() > art.width) { // 如果当前行的长度大于宽度
                art.width = line.size(); // 更新宽度为当前行的长度
            }
        }
        file.close(); // 关闭文件
    }
    return art; // 返回ASCII艺术字结构体
}

// 定义一个函数，用于在控制台上显示ASCII艺术字，并修改背景字符为相同颜色的空格
void show_ascii_art(const ASCIIArt& art, int x, int y, WORD color, std::vector<std::string>& background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    COORD coord; // 定义一个坐标结构体，用于设置光标位置
    coord.X = x; // 设置横坐标为x
    coord.Y = y; // 设置纵坐标为y
    SetConsoleCursorPosition(hConsole, coord); // 设置光标位置
    for (int i = 0; i < art.height; i++) { // 循环遍历每一行
        SetConsoleTextAttribute(hConsole, color); // 设置文本颜色为color
        std::cout << art.lines[i] << std::endl; // 输出当前行，并换行
        for (int j = 0; j < art.width; j++) { // 循环遍历每一列
            if (art.lines[i][j] != ' ') { // 如果当前位置不是空格，说明是ASCII艺术字的一部分
                background[y + i][x + j] = ' '; // 将背景字符替换为空格
            }
        }
        coord.Y++; // 纵坐标加1
        SetConsoleCursorPosition(hConsole, coord); // 设置光标位置
    }
}

// 定义一个函数，用于生成灰色的字符填充背景，并模拟代码雨下落的效果
void show_rain_background(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    COORD coord; // 定义一个坐标结构体，用于设置光标位置
    coord.X = 0; // 设置横坐标为0
    coord.Y = 0; // 设置纵坐标为0
    SetConsoleOutputCP(65001);
    char val[] = "黑框框";
    std::vector<std::string> background(height); // 定义一个字符串向量，用于存储背景的每一行

    srand(time(NULL)); // 设置随机数种子

    for (int i = 0; i < height; i++) { // 循环遍历每一行
        for (int j = 0; j < width; j++) { // 循环遍历每一列
            // 随机生成一个ASCII码在0到3之间的字符，作为背景的填充
            // 将字符添加到当前行的字符串中
            background[i].push_back('#');
        }
    }

    // 定义一个整数向量，用于存储每一列的代码雨的长度
    std::vector<int> rain_length(width);
    // 定义一个整数向量，用于存储每一列的代码雨的当前位置
    std::vector<int> rain_position(width);

    for (int j = 0; j < width; j++)
    { // 循环遍历每一列

        // 随机生成一个代码雨的长度，范围在2到5之间
        rain_length[j] = 1;
        // 随机生成一个代码雨的当前位置，范围在0到height之间
        rain_position[j] = j;
    }
    int t = 15;
    while (t--) { // 无限循环，模拟代码雨不断下落的效果
        Sleep(100);
        for (int i = 0; i < height; i++) { // 循环遍历每一行
            SetConsoleCursorPosition(hConsole, coord); // 设置光标位置

            for (int j = 0; j < width; j++) { // 循环遍历每一列
                if (i >= rain_position[j] && i < rain_position[j] + rain_length[j]) {
                    // 如果当前位置在代码雨的范围内，就设置文本颜色为绿色
                    background[i][j] = '.';
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                }
                else {
                    // 否则，就设置文本颜色为灰色
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                // 输出当前位置的字符

                std::cout << background[i][j];
            }
            std::cout << std::endl; // 换行
            coord.Y++; // 纵坐标加1
        }
        coord.Y = 0; // 纵坐标重置为0

        for (int j = 0; j < width; j++) { // 循环遍历每一列
            // 更新代码雨的当前位置，如果超出了高度，就重置为0
            rain_position[j] = (rain_position[j] + 1) % height;
        }

        Sleep(100); // 延迟100毫秒，模拟动画效果
    }
}

// 定义主函数，用于测试上述函数
int codeRain() {
    ASCIIArt art = read_ascii_art("ascii_art.txt"); // 从文件中读取ASCII艺术字

    int width = 74; // 定义控制台的宽度（字符数）
    int height = 7; // 定义控制台的高度（行数）

    std::vector<std::string> background(height); // 定义一个字符串向量，用于存储背景的每一行

    show_rain_background(width, height); // 在控制台上显示灰色的字符填充背景，并模拟代码雨下落的效果

    int x = (width - art.width) / 2; // 计算ASCII艺术字的横坐标，使其居中显示
    int y = (height - art.height) / 2; // 计算ASCII艺术字的纵坐标，使其居中显示

    show_ascii_art(art, x, y, FOREGROUND_GREEN, background); // 在控制台上显示ASCII艺术字，并修改背景字符为相同颜色的空格
    return 0; // 返回0，表示程序正常结束
}
int valchat()
{
    Sleep(4000);
    gotoxy(0, 0);
    PlaySound(TEXT("C:\\Users\\yangluwei\\source\\repos\\valclient\\valclient\\正确-系统提示游戏提示_爱给网_aigei_com.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
    PlaySound(TEXT("D:\\下载\\ewsfm-yslvo .wav"), NULL, SND_FILENAME | SND_ASYNC);;
}