#pragma once
/*
	资源背景：宽46高56
	资源人物：宽39高39
*/
#include<stdio.h>
#include<graphics.h>
#include<time.h>

#define MAP_ROW 10	
#define MAP_COL 10
#define MAP_SIZE ( MAP_ROW - 2 ) * ( MAP_COL - 2 )	//地图大小

int g_map[MAP_ROW][MAP_COL] = { 0 };
IMAGE g_block;	//背景图片
IMAGE g_animal;	//动物图片

int g_randSize = 10;	//资源图片有42张图 随机范围为1~42 可自行设计难度

int    g_clickIndex = 0;			//点击的下标
COORD  g_targetPos[2] = { -1, -1 };	//点击的两个位置

int	   g_score = MAP_SIZE;		//成绩

void InitGame();
void UpdateGame();
void DrawGame();

void IsWin();

bool HavePath(COORD targetPos[]);
bool HavePathCorner0(COORD p1, COORD p2);	//没有转折点
bool HavePathCorner1(COORD p1, COORD p2);	//一个转折点
bool HavePathCorner2(COORD p1, COORD p2);	//两个转折点


void play7()
{
	/*定义一个随机种子*/
	srand((unsigned int)time(NULL));

	/*创建一个窗口*/
	initgraph(MAP_COL * 46, MAP_ROW * 56);
	InitGame();
	DrawGame();
	while (1)
	{
		UpdateGame();
		DrawGame();
		IsWin();
	}
}

void InitGame()
{
	/*加载图片的资源*/
	/*加载方块*/
	loadimage(&g_block, "./res/block.jpg");

	/*加载动物*/
	loadimage(&g_animal, "./res/animal.jpg");

	/*初始化变量*/
	int tempMap[MAP_SIZE] = { 0 };
	/*随机生成地图数据*/
	for (int i = 0; i < MAP_SIZE / 2; i++)
	{
		tempMap[i] = rand() % g_randSize + 1;       /*随机[1 - 10]*/
		tempMap[MAP_SIZE / 2 + i] = tempMap[i];
	}
	/*打乱数据*/
	for (int i = 0; i < MAP_SIZE; i++)
	{
		int index = rand() % MAP_SIZE;
		if (index != i)
		{
			int temp = tempMap[i];
			tempMap[i] = tempMap[index];
			tempMap[index] = temp;
		}
	}
	/*转成一个二维地图数组*/
	int index = 0;
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			if (i == 0 || i == MAP_ROW - 1 || j == 0 || j == MAP_COL - 1)
			{
				g_map[i][j] = 0;
			}
			else
			{
				g_map[i][j] = tempMap[index++];
			}
		}
	}
}

bool HavePathCorner0(COORD p1, COORD p2)
{
	/*判断两张图片是否在一条直线上，不是，直接返回false*/
	if (p1.X != p2.X && p2.Y != p1.Y)
		return false;
	/*为什么求最大值，最小值
	  因为：给的参数，不清楚你的p1,p2的坐标谁最大*/

	int min = 0, max = 0;
	/*竖向：判断竖向是否都为空*/
	if (p1.X == p2.X)
	{
		min = p1.Y < p2.Y ? p1.Y : p2.Y;
		max = p1.Y > p2.Y ? p1.Y : p2.Y;
		for (min++; min < max; min++)
		{
			if (g_map[min][p1.X] != 0)
				return false;
		}
	}

	/*横向：判断横向是否都为空*/
	if (p1.Y == p2.Y)
	{
		min = p1.X < p2.X ? p1.X : p2.X;
		max = p1.X > p2.X ? p1.X : p2.X;
		for (min++; min < max; min++)
		{
			if (g_map[p1.Y][min] != 0)
				return false;
		}
	}
	return true;
}

bool HavePathCorner1(COORD p1, COORD p2)
{
	//解决两个转折点遗留问题
	if (p1.X == p2.X || p1.Y == p2.Y)
		return false;

	//找到转折点
	COORD temp[2];	//两个目标是转折点
	temp[0].X = p1.X;
	temp[0].Y = p2.Y;
	temp[1].X = p2.X;
	temp[1].Y = p1.Y;
	//判断第一个转折点是否连通
	if (g_map[temp[0].Y][temp[0].X] == 0)
	{
		if (HavePathCorner0(p1, temp[0]) == true && HavePathCorner0(p2, temp[0]) == true)
		{
			line(p1.X * 46 + 23, p1.Y * 56 + 28, temp[0].X * 46 + 23, temp[0].Y * 56 + 28);
			line(p2.X * 46 + 23, p2.Y * 56 + 28, temp[0].X * 46 + 23, temp[0].Y * 56 + 28);
			return true;
		}
	}
	//判断第二个转折点是否连通
	if (g_map[temp[1].Y][temp[1].X] == 0)
	{
		if (HavePathCorner0(p1, temp[1]) == true && HavePathCorner0(p2, temp[1]) == true)
		{
			line(p1.X * 46 + 23, p1.Y * 56 + 28, temp[1].X * 46 + 23, temp[1].Y * 56 + 28);
			line(p2.X * 46 + 23, p2.Y * 56 + 28, temp[1].X * 46 + 23, temp[1].Y * 56 + 28);
			return true;
		}

	}

	return false;
}

bool HavePathCorner2(COORD p1, COORD p2)
{
	COORD temp;

	//任取一目标，往上找
	for (temp.Y = p1.Y - 1, temp.X = p1.X; temp.Y >= 0; temp.Y--)
	{
		//如果往上找直到找到不为空的就结束，或者找到顶了
		if (g_map[temp.Y][temp.X] != 0)
			break;
		//可以判断temp点到p1点是一路为空的，只需要判断p2点和temp是否为只有一个转折点就可以
		if (HavePathCorner1(p2, temp))
		{
			line(p1.X * 46 + 23, p1.Y * 56 + 28, temp.X * 46 + 23, temp.Y * 56 + 28);
			return true;
		}
	}
	//任取一目标，往下找
	for (temp.Y = p1.Y + 1, temp.X = p1.X; temp.Y < MAP_ROW; temp.Y++)
	{
		//如果往下找直到找到不为空的就结束，或者找到顶了
		if (g_map[temp.Y][temp.X] != 0)
			break;
		//可以判断temp点到p1点是一路为空的，只需要判断p2点和temp是否为只有一个转折点就可以
		if (HavePathCorner1(p2, temp))
		{
			line(p1.X * 46 + 23, p1.Y * 56 + 28, temp.X * 46 + 23, temp.Y * 56 + 28);
			return true;
		}
	}

	//任取一目标，往左找
	for (temp.X = p1.X - 1, temp.Y = p1.Y; temp.X >= 0; temp.X--)
	{
		//如果往左找直到找到不为空的就结束，或者找到顶了
		if (g_map[temp.Y][temp.X] != 0)
			break;
		//可以判断temp点到p1点是一路为空的，只需要判断p2点和temp是否为只有一个转折点就可以
		if (HavePathCorner1(p2, temp))
		{
			line(p1.X * 46 + 23, p1.Y * 56 + 28, temp.X * 46 + 23, temp.Y * 56 + 28);
			return true;
		}
	}
	//任取一目标，往右找
	for (temp.X = p1.X + 1, temp.Y = p1.Y; temp.X < MAP_COL; temp.X++)
	{
		//如果往下找直到找到不为空的就结束，或者找到顶了
		if (g_map[temp.Y][temp.X] != 0)
			break;
		//可以判断temp点到p1点是一路为空的，只需要判断p2点和temp是否为只有一个转折点就可以
		if (HavePathCorner1(p2, temp))
		{
			line(p1.X * 46 + 23, p1.Y * 56 + 28, temp.X * 46 + 23, temp.Y * 56 + 28);
			return true;
		}
	}

	return false;
}

bool HavePath(COORD targetPos[])
{
	/*没有转折点*/
	if (HavePathCorner0(targetPos[0], targetPos[1]) == true)
	{
		line(g_targetPos[0].X * 46 + 23, g_targetPos[0].Y * 56 + 28, g_targetPos[1].X * 46 + 23, g_targetPos[1].Y * 56 + 28);
		return true;
	}
	/*有一个转折点*/
	if (HavePathCorner1(targetPos[0], targetPos[1]) == true)
	{
		return true;
	}
	/*有两个转折点*/
	if (HavePathCorner2(targetPos[0], targetPos[1]) == true)
	{
		return true;
	}
	return false;
}

void UpdateGame()
{
	/*鼠标消息*/
	MOUSEMSG msg = GetMouseMsg();
	int row = msg.y / 56;
	int col = msg.x / 45;
	switch (msg.uMsg)		/*msg.uMsg得到一个鼠标消息*/
	{
	case WM_LBUTTONDOWN:    /*鼠标左键按下*/
		if (g_map[row][col] == 0)
			break;
		g_targetPos[g_clickIndex].X = col;    /*下标：0，1，超出了就越界*/
		g_targetPos[g_clickIndex].Y = row;
		if (++g_clickIndex > 1)
		{
			g_clickIndex = 0;
			/*点击一张图片两下，不消除，直接返回*/
			if (g_targetPos[0].X == g_targetPos[1].X && g_targetPos[0].Y == g_targetPos[1].Y)
				return;
			/*点击两张图片，判断鼠标两个坐标的位置值不相等，直接返回*/
			if (g_map[g_targetPos[0].Y][g_targetPos[0].X] != g_map[g_targetPos[1].Y][g_targetPos[1].X])
			{
				g_clickIndex = 1;
				g_targetPos[0] = g_targetPos[1];
				return;
			}

			/*进行消除操作*/
			if (HavePath(g_targetPos) == true)
			{
				rectangle(g_targetPos[1].X * 46 + 4, g_targetPos[1].Y * 56 + 4, g_targetPos[1].X * 46 + 36, g_targetPos[1].Y * 56 + 44);
				Sleep(100);
				for (int i = 0; i < 2; i++)
				{
					g_map[g_targetPos[i].Y][g_targetPos[i].X] = 0;
				}
				g_score -= 2;
			}
			else
			{	//消除失败
				g_targetPos[0] = g_targetPos[1];
				g_clickIndex = 1;
			}
		}
		break;
	}
}

void DrawGame()
{
	BeginBatchDraw();
	//putimage(0	// 绘制位置的 x 坐标
	//	, 0		// 绘制位置的 y 坐标
	//	, 46	// 绘制的宽度
	//	, 56	// 绘制的高度
	//	, &g_block	// 要绘制的 IMAGE 对象指针
	//	, 0			// 绘制内容在 IMAGE 对象中的左上角 x 坐标
	//	, 56 * 0	// 绘制内容在 IMAGE 对象中的左上角 y 坐标
	//);	// 392/7=56
	/*绘制方块*/
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			putimage(j * 46, i * 56, 46, 56, &g_block, 0, 56, SRCCOPY);
		}
	}
	/*绘制动物*/
	for (int i = 1; i < MAP_ROW - 1; i++)
	{
		for (int j = 1; j < MAP_COL - 1; j++)
		{
			/*不等于0，绘制动物，等于0，什么都不绘制 动物图片大小为39 * 39 */
			if (g_map[i][j] != 0)
			{
				putimage(j * 46 + 1.5, i * 56 + 6, 39, 39, &g_animal, 39, (g_map[i][j] - 1) * 39, SRCAND);
				putimage(j * 46 + 1.5, i * 56 + 6, 39, 39, &g_animal, 0, (g_map[i][j] - 1) * 39, SRCPAINT);
			}
		}
	}
	setlinecolor(GREEN);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);	//画线样式为宽度 3 像素的实线，端点为平坦的
	if (g_clickIndex > 0)
	{
		rectangle(g_targetPos[0].X * 46 + 4, g_targetPos[0].Y * 56 + 4, g_targetPos[0].X * 46 + 36, g_targetPos[0].Y * 56 + 44);
	}
	EndBatchDraw();
}

void IsWin()
{
	int op;
	//判断输赢
	if (g_score <= 0)
	{
		op = MessageBox(GetHWnd(), "恭喜完成挑战,是否进入下一关", "Vectory", MB_YESNO | MB_DEFBUTTON1);
		if (op == IDYES)
		{
			if (g_randSize >= 40)
			{
				MessageBox(GetHWnd(), "恭喜通关成功", "Vectory", MB_OK);
				exit(0);
			}
			g_randSize += 5;
			g_score = MAP_SIZE;
			InitGame();
			DrawGame();
		}
		else
		{
			exit(0);	//退出游戏
		}
	}
}
