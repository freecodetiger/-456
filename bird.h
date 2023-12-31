#pragma once
#include"stdio.h"
#include"windows.h"
#include"string.h"
#include"conio.h"
#include"time.h"

typedef struct pipe
{
	int x;
	int y;
	struct pipe* next;
}PIPE;

// 定义一个二维数组，用来存储背景图片
char backGround[14][80] = { 0 };
// 定义一个变量，用来存储当前的时间
int  Time = 0;
// 定义一个变量，用来存储当前的分数
unsigned int  Score = 0;

// 隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 移动光标到指定位置
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Getready()
{
	int i = 0, j = 0;

	// 初始化背景
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 80; j++)
		{
			backGround[i][j] = ' ';
		}
	}
	// 打印上边框
	for (i = 0; i < 8; i++)
	{
		(backGround, "  ┌┐    ");
	}
	// 打印左边框
	for (i = 0; i < 8; i++)
	{
		(backGround, "┌┤│    ");
	}
	// 打印下边框
	for (i = 0; i < 8; i++)
	{
		(backGround, "││├┐  ");
	}


	// 打印标题
	gotoxy(30, 3);
	printf("G e t  R e a d y");

	// 打印进度条
	gotoxy(0, 14);
	for (i = 0; i < 40; i++)
	{
		printf("▁");
		printf(" ");
		printf(" ");
	}
	for (i = 0; i < 11; i++)
	{
		printf("  ╱╱ ");
	}
	gotoxy(0, 16);
	for (i = 0; i < 40; i++)
	{
		printf("▔");
	}
	// 打印按钮
	gotoxy(18, 3);
	printf("*@>");
	_getch();
	// 打印空行
	gotoxy(30, 3);
	printf("                ");



}

PIPE* Pipefun(PIPE* h)
{
	// 定义变量i，j，p，用于循环
	int i = 0, j = 0;
	PIPE* p;

	// 循环6次，每次循环打印一行，并判断是否需要打印下一行
	for (p = h, i = 0; i < 6; i++)
	{
		for (j = 0; j < 14; j++)
		{
			// 如果j等于当前行的y坐标减1，或者等于当前行的y坐标，或者等于当前行的y坐标加1，则跳过本次循环
			if (j == p->y - 1 || j == p->y || j == p->y + 1)
				continue;
			else
			{
				// 如果当前行的x坐标大于等于0，且小于80，则打印当前行的x坐标和j坐标的字符
				if (p->x >= 0 && p->x < 80)
					gotoxy(p->x, j), printf("■");
				// 如果当前行的x坐标加上2大于等于0，且小于80，则打印当前行的x坐标加上2和j坐标的字符
				if (p->x + 2 >= 0 && p->x + 2 < 80)
					gotoxy(p->x + 2, j), printf("■");
				// 如果当前行的x坐标加上4大于等于0，且小于80，则打印当前行的x坐标加上4和j坐标的字符
				if (p->x + 4 >= 0 && p->x + 4 < 80)
					gotoxy(p->x + 4, j), printf("%c%c", backGround[j][p->x + 4], backGround[j][p->x + 5]);
			}
		}
		// 每次循环将当前行的x坐标减2
		p->x = p->x - 2;
		// 将当前行赋值给p，p指向下一行
		p = p->next;
	}

	// 如果当前行的x坐标小于-4，则将当前行的x坐标赋值为78+12，将当前行的y坐标赋值为随机数，将当前行赋值给h，h指向下一行
	if (h->x < -4)
	{
		h->x = 78 + 12;
		h->y = rand() % 9 + 3;
		h = h->next;
	}

	// 返回h
	return h;
}

// 定义变量i，bird，temp，ch，用于循环
void Bird()
{
	// 定义变量i，bird，temp，ch，用于循环
	int  i = 0, bird = 3, temp = 0;
	char ch = '0';
	PIPE* h, * p, * q;

	// 定义h，p，q，用于循环
	p = h = q = (PIPE*)malloc(sizeof(PIPE));
	// 循环5次，每次循环将当前行的x坐标赋值为78+16*i，将当前行的y坐标赋值为随机数，将当前行赋值给q，q指向下一行
	for (i = 0; i < 5; i++)
	{
		p->x = 78 + 16 * i;
		p->y = rand() % 9 + 3;
		q = (PIPE*)malloc(sizeof(PIPE));
		p->next = q;
		q->next = NULL;
		p = q;
		q->next = h;
		q = q->next;
	}
	// 将当前行的x坐标赋值为78+16*i，将当前行的y坐标赋值为随机数
	p->x = 78 + 16 * i;
	p->y = rand() % 13 + 1;
	// 将当前行赋值给q，q指向下一行
	q->next = h;
	while (1)
	{
		// 每次循环，时间加1
		Time++;

		// 保存当前的鸟的位置
		temp = bird;

		// 如果按下键盘上的键，则改变鸟的位置
		if (_kbhit())
			ch = _getch();

		// 如果按下空格键，鸟向上移动，否则向下移动
		ch == ' ' ? bird-- : bird++;
		ch = '0';

		// 如果鸟的位置超出范围，则结束游戏
		if (bird < 0 || bird >= 14)
			break;

		// 打印背景
		gotoxy(18, temp);
		printf("  %c%c", backGround[temp][20], backGround[temp][21]);
		gotoxy(18, bird);
		printf("*@>");

		// 如果时间除以3的余数为1，则调用Pipefun函数，改变管道的高度
		if (Time % 3 == 1)
			h = Pipefun(h);
		// 遍历管道，如果管道的高度等于鸟的位置，则结束游戏
		for (p = h, i = 0; i < 6; i++, p = p->next)
			if (p->x == 18 && p->y - 1 != bird && p->y != bird && p->y + 1 != bird)
				break;
		// 如果管道的高度等于鸟的位置，则结束游戏
		if (p->x == 18 && p->y - 1 != bird && p->y != bird && p->y + 1 != bird)
			break;

		// 每次循环暂停300毫秒
		Sleep(300);
	}
}

void Gameover()
{
	// 如果游戏结束，则计算得分
	Score = (Time - 88) / 24 < 0 ? 0 : (Time - 88) / 24;
	// 打印游戏结束信息
	gotoxy(28, 5);
	printf("┌──────────┐");
	gotoxy(28, 6);
	printf("│   G A M E O V E R  │");
	gotoxy(28, 7);
	printf("│                    │");
	gotoxy(28, 8);
	printf("│             %4d   │", Score);
	gotoxy(28, 9);
	printf("└──────────┘");

}
void play4()
{
	//隐藏光标
	HideCursor();
	//设置窗口标题
	system("title Flappy Bird");
	//设置窗口大小
	system("mode con cols = 80 lines = 20");
	//设置随机种子
	srand((unsigned)time(NULL));

	//调用准备函数
	Getready();
	//调用鸟函数
	Bird();
	//调用游戏结束函数
	Gameover();

	//等待按键按下
	_getch();
}
