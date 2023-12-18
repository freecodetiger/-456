//#pragma once
#ifndef MINESWEEP_H
#define MINESWEEP_H
#include<stdio.h>
#include<graphics.h>
#include<time.h>
//地图大小 用map_row map_col控制地图大小
	int map_row, map_col;
//翻开的次数
	int times;
//雷的数量
	int mine;	
//判断是否失败
	int isfail;	
//雷的数量达到10% 就扩大游戏区域
	int pass;	
	//当前窗口
	HWND hWnd;
	int map[30][30] = { 0 };	//地图	用map_row map_col控制地图大小
	IMAGE imgs[14];	//图片
	/**************全局函数**************/
	void init();
	void DrawMap();
	//赢了之后初始化游戏数据 更新地图
	void initmap();
	void Play();
	//判断玩家是否获胜
	void Judg();
	//打开无雷格子需要调用的特殊函数
	void Empty(int row, int col);
	void play1()
	{
		//数据初始化
		init();
		//绘图
		DrawMap();
		while (1)
		{
			Play();
			Judg();
		}
		getchar();
		closegraph();
		//return 0;
	}

	void init()
	{
		//设置随机数种子
		srand((unsigned)time(NULL));
		map_row = 10;	//地图行
		map_col = 10;	//地图列
		isfail = 0;
		pass = 0;
		//加载图片
		loadimage(&imgs[0], "素材/0.bmp", 25, 25);
		loadimage(&imgs[1], "素材/1.bmp", 25, 25);
		loadimage(&imgs[2], "素材/2.bmp", 25, 25);
		loadimage(&imgs[3], "素材/3.bmp", 25, 25);
		loadimage(&imgs[4], "素材/4.bmp", 25, 25);
		loadimage(&imgs[5], "素材/5.bmp", 25, 25);
		loadimage(&imgs[6], "素材/6.bmp", 25, 25);
		loadimage(&imgs[7], "素材/7.bmp", 25, 25);
		loadimage(&imgs[8], "素材/8.bmp", 25, 25);
		loadimage(&imgs[9], "素材/标记.bmp", 25, 25);
		loadimage(&imgs[10], "素材/空.bmp", 25, 25);
		loadimage(&imgs[11], "素材/雷0.bmp", 25, 25);
		loadimage(&imgs[12], "素材/雷1.bmp", 25, 25);
		loadimage(&imgs[13], "素材/雷2.bmp", 25, 25);

		initmap();
	}

	void DrawMap()
	{
		BeginBatchDraw();
		for (int y = 1; y <= map_row; y++)
		{
			for (int x = 1; x <= map_col; x++)
			{
				if (map[y][x] > 18)
				{
					//标记部分额外处理
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[9]);
					continue;
				}
				switch (map[y][x])
				{
					// -1 + 10 = 9 踩到雷了
				case 9:		
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[13]);
					isfail = 1;
					break;
					//空白
				case 10:
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[0]);
					break;
					//有一个雷
				case 11:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[1]);
					break;
					//有两个雷
				case 12:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[2]);
					break;
					//有三个雷
				case 13:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[3]);
					break;
					//有四个雷
				case 14:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[4]);
					break;
					//有五个雷
				case 15:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[5]);
					break;
					//有六个雷
				case 16:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[6]);
					break;
					//有七个雷
				case 17:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[7]);
					break;
					//有八个雷
				case 18:	
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[8]);
					break;
					//其余情形为未翻开
				default:
					putimage((x - 1) * 25, (y - 1) * 25, &imgs[10]);
					break;
				}
			}
		}
		EndBatchDraw();
	}

	void initmap()
	{
		//Zero memory函数可以指定一段存储区域被填充为0，比遍历数组更快
		ZeroMemory(map, sizeof(int) * 30 * 30);		//初始化地图为0
		//翻开次数
		times = 0;
		//每次获胜后调用initmap函数，雷的数量 + 5
		mine += 5;
		float x = mine / (float)(map_row * map_col);
		if (x > 0.15)
		{
			//当雷的数量达到10%时扩大游戏区域	先横向扩大5个后纵向扩大5个
			if (pass++ % 2)		//使 pass 在 0 和 1之间变换		首先是0 ，然后0 1 之间循环
			{
				map_row += 5;	//纵向扩大5个区域
			}
			else
			{
				map_col += 5;	//横向扩大5个区域
			}
		}
		//初始化地图大小
		hWnd = initgraph(map_col * 25, map_row * 25);		
		//雷所在的行和列数
		int mine_r, mine_c;
		//随机在地图中布置地雷（数目为mine）
		for (int i = 0; i < mine;)
		{
			mine_r = rand() % map_row + 1;	//mine_r 1 ~ 8
			mine_c = rand() % map_col + 1;
			//已经有雷的地方就不放了
			if (map[mine_r][mine_c] == 0)
			{
				//在数组中放雷，-1表示有雷
				map[mine_r][mine_c] = -1;
				//放入雷后雷的数量加一
				i++;						
			}
		}
		//给雷附近的数加一
		for (int i = 1; i <= map_row; i++)
		{
			for (int j = 1; j <= map_col; j++)
			{
				//如果这个地方没有雷，就根据周围的雷的数目填充对应的数字
				if (map[i][j] != -1)
				{
					//检查周围雷的个数
					for (int m = i - 1; m <= i + 1; m++)
					{
						for (int n = j - 1; n <= j + 1; n++)
						{
							if (map[m][n] == -1) {	
								//附近有雷，数字加一
								map[i][j]++;
							}
						}
					}
				}
			}
		}
		//字符数组用来存储窗口标题
		char arr[20];
		//设置窗口标题，标题上显示雷的数量
		wsprintf(arr, "扫雷 雷:%d", mine);
		SetWindowText(hWnd, arr);
	}

	void Play()
	{
		//鼠标交互操作
		MOUSEMSG msg;//鼠标消息
		int row, col;//鼠标点击的行和列
		msg = GetMouseMsg();
		row = msg.y / 25 + 1;
		col = msg.x / 25 + 1;
		switch (msg.uMsg)
		{
			//如果左键按下
		case WM_LBUTTONDOWN:
			//翻开过的 和标记的 不进行操作
			if (map[row][col] >= 9)
			{
				break;
			}
			//翻开 0项 和 周围的图片
			if (map[row][col] == 0)
			{
				Empty(row, col);
			}
			else//翻开点击的区块
			{
				map[row][col] += 10;//翻开
				times++;	//翻开次数 +1
			}
			break;
		case WM_RBUTTONDOWN://右键按下 WM_RBUTTONDOWN
			//已经翻开的不进行操作
			if (map[row][col] >= 9 && map[row][col] < 19)
			{
				break;
			}
			if (map[row][col] >= 19)//标记的取消标记
			{
				map[row][col] -= 20;
			}
			else//没有翻开的加20
			{
				map[row][col] += 20;	//20是随意的数字，只要足够大就行
			}
			break;
		}
		DrawMap();
	}

	void Judg()
	{
		//先查找是否点开了雷
		if (isfail)
		{
			//显示一个带有两个按钮的消息框：“是”和“否”。
			// 如果用户点击了“是”，程序会重新开始当前关卡。如果用户点击了“否”，程序退出。
			if (MessageBox(GetHWnd(), "你踩到雷了,是否重新开始本关", "失败", MB_YESNO) == IDYES)		//GetHWnd()是获取一个顶置窗口
			{
				mine -= 5;//雷的数目减少5个和initmap中的增加5个抵消
				isfail = 0;
				initmap();
				//渲染地图
				DrawMap();	
			}
			else
			{
				//按“否”就退出游戏
				_exit(0);
			}
		}

		if (times == map_row * map_col - mine)	//所有点 - 雷 = 非雷区
		{
			if (MessageBox(GetHWnd(), "是否进入下一关", "成功", MB_YESNO) == IDYES) {
				closegraph();
				//重新开始游戏
				initmap();
				//渲染地图
				DrawMap();	
			}
			else {
				_exit(0);
			}
		}
	}

	void Empty(int row, int col)
	{
		//递归实现以 0 为 九宫格的区域 自动翻开
		map[row][col] += 10;	//翻开当前位置
		times++;				//翻开次数+1
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				//外圈空白区域不操作	仅对可以看到的区域进行递归调用
				if (i >= 1 && i <= map_row && j >= 1 && j <= map_col)
				{
					if (map[i][j] < 9)			//小于9 是未操作，未翻开的区域
					{
						//0的周围九宫格内无雷，翻开
						if (map[i][j] == 0)		
						{
							Empty(i, j);
						}
						else
						{
							//有雷的不翻，让玩家思考是否需要翻开
							map[i][j] += 10;	
							times++;
						}
					}
				}
			}
		}
	}
#endif
