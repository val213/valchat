#include"ui.h"
void randomcolor()
{
	random_device rd_h; //Ӳ���������������

	mt19937 eng01(rd_h()); //���������������������
	uniform_int_distribution<int> color(0, 15); //�����������Χ����Ϊ���ȷֲ�
	int bgcolor = color(eng01);
	switch (bgcolor)
	{
	case 0:system("color 01"); break;
	case 1:system("color 10"); break;
	case 2:system("color 20"); break;
	case 3:system("color 3C"); break;
	case 4:system("color 4F"); break;
	case 5:system("color 5E"); break;
	case 6:system("color 69"); break;
	case 7:system("color 76"); break;
	case 8:system("color 8F"); break;
	case 9:system("color 90"); break;
	case 10:system("color A0"); break;
	case 11:system("color B0"); break;
	case 12:system("color CF"); break;
	case 13:system("color 4A"); break;
	case 14:system("color E0"); break;
	case 15:system("color F0"); break;
	}
}
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}

void SetColor(int& fore, int& back)
{
	random_device rd_h; //Ӳ���������������

	mt19937 eng01(rd_h()); //���������������������
	uniform_int_distribution<int> forecolor(0, 15); //�����������Χ����Ϊ���ȷֲ�
	fore = forecolor(eng01);


	mt19937 eng02(rd_h()); //���������������������
	uniform_int_distribution<int> backcolor(0, 15); //�����������Χ����Ϊ���ȷֲ�
	back = backcolor(eng02);

	switch (back)
	{
	case 0:system("color 01"); break;
	case 1:system("color 10"); break;
	case 2:system("color 20"); break;
	case 3:system("color 3F"); break;
	case 4:system("color 4F"); break;
	case 5:system("color 5F"); break;
	case 6:system("color 6F"); break;
	case 7:system("color 70"); break;
	case 8:system("color 80"); break;
	case 9:system("color 90"); break;
	case 10:system("color A0"); break;
	case 11:system("color B0"); break;
	case 12:system("color CF"); break;
	case 13:system("color D0"); break;
	case 14:system("color E0"); break;
	case 15:system("color F0"); break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (back << 4) + fore);
}
void errmusic()
{
	PlaySound(TEXT("D:\\����\\f1xn4-w5rnt.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
