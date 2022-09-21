#include "main.h"

//=======================================================
// Console ȭ�鿡 ���õ� �Լ�
//=======================================================
void gotoxy(short x, short y)	// Ŀ�� ��ġ ����
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcolor(int colFront, int colBack)	//���ڻ�,���� ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(colFront | (colBack << 4)));
}
void removeCursor(void)			// Ŀ�� �����̴°� �����
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

