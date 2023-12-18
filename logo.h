#pragma once
#include <graphics.h>  // 引入EasyX图形库
#include <conio.h>//引入getch函数
double PI = 3.14159265358979323846;
void logo() {
    initgraph(400, 400);  // 创建一个400x400的窗口，对应40x40的方格纸

    // 绘制方格
    for (int i = 0; i <= 400; i += 10) {
        line(0, i, 400, i);  // 横线
        line(i, 0, i, 400);  // 竖线
    }

    // 绘制笑脸

    setfillcolor(BLUE);  // 设置填充颜色为黄色
    setlinecolor(BLACK);   // 设置线条颜色为黑色
    int x;
    int y;
    int xradius;
    int yradius;

    // 绘制圆脸
    x = 50, y = 50, xradius = 350, yradius = 350;
    fillellipse(x, y, xradius, yradius);

    // 绘制眼睛
    setfillcolor(GREEN);  // 设置填充颜色为白色
    x = 75, y = 125, xradius = 175, yradius = 275;
    fillellipse(x, y, xradius, yradius);  // 左眼
    x = 250, y = 150, xradius = 325, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 右眼

    // 绘制鼻子
    setlinecolor(RED);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    int left = 225;
    int right = 180;
    int top = 175;
    int bottom = 280;
    int strangle = 200;
    int endangle = 359;
    arc(left, top, right, bottom, strangle, endangle);  // 绘制弧线，表示鼻子
    //绘制嘴巴
    setlinecolor(BROWN);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    left = 225;
    right = 180;
    top = 325;
    bottom = 300;
    strangle = 200;
    endangle = 359;
    arc(left, top, right, bottom, strangle, endangle);  // 绘制弧线，表示嘴巴
    Sleep(1000);

    //_getch();  // 等待用户按任意键退出
    closegraph();  // 关闭图形窗口
    //return 0;
}
void logo2() {
    initgraph(400, 400);  // 创建一个400x400的窗口，对应40x40的方格纸

    // 绘制方格
    for (int i = 0; i <= 400; i += 10) {
        line(0, i, 400, i);  // 横线
        line(i, 0, i, 400);  // 竖线
    }

    // 绘制笑脸

    setfillcolor(0xFFFFFF);  // 设置填充颜色为黄色
    setlinecolor(RED);   // 设置线条颜色为黑色
    int x;
    int y;
    int xradius;
    int yradius;

    // 绘制圆脸
    x = 50, y = 50, xradius = 350, yradius = 350;
    fillellipse(x, y, xradius, yradius);

    // 绘制眼睛
    setfillcolor(0xFF55FF);  // 设置填充颜色为白色
    x = 75, y = 150, xradius = 175, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 左眼
    x = 225, y = 150, xradius = 325, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 右眼

    // 绘制瞳孔
    setfillcolor(0xAA0000);
    setlinecolor(RED);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    int left = 100;
    int right = 150;
    int top = 100;
    int bottom = 225;
    double strangle = 4 * PI / 3;
    double endangle = 5 * PI / 3;
    solidpie(left, top, right, bottom, strangle, endangle);  // 绘制扇形，表示瞳孔
    left = 250;
    right = 300;
    solidpie(left, top, right, bottom, strangle, endangle);
    //绘制嘴巴
    setfillcolor(0xFFFFFF);
    left = 125;
    right = 275;
    top = 275;
    bottom = 325;
    int ellipsewidth = 25;
    int ellipseheight = 25;
    fillroundrect(left, top, right, bottom, ellipsewidth, ellipseheight);  // 绘制弧线，表示嘴巴
    Sleep(1000);
    //_getch();  // 等待用户按任意键退出
    closegraph();  // 关闭图形窗口
    //return 0;
}
void logo3() {
    initgraph(400, 400);  // 创建一个400x400的窗口，对应40x40的方格纸

    // 绘制方格
    for (int i = 0; i <= 400; i += 10) {
        line(0, i, 400, i);  // 横线
        line(i, 0, i, 400);  // 竖线
    }

    // 绘制笑脸

    setfillcolor(0xFFFFFF);  // 设置填充颜色为黄色
    setlinecolor(RED);   // 设置线条颜色为黑色
    int x;
    int y;
    int xradius;
    int yradius;

    // 绘制圆脸
    x = 50, y = 50, xradius = 350, yradius = 350;
    fillellipse(x, y, xradius, yradius);

    // 绘制眼睛
    setfillcolor(BLACK);  // 设置填充颜色为白色
    x = 75, y = 150, xradius = 175, yradius = 225;
    fillrectangle(x, y, xradius, yradius);  // 左眼
    x = 225, y = 150, xradius = 325, yradius = 225;
    fillrectangle(x, y, xradius, yradius);  // 右眼
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 10);
    int x1 = 175;
    int y1 = 187;
    int x2 = 225;
    int y2 = 187;
    line(x1, y1, x2, y2);
    // 绘制瞳孔
    setfillcolor(0xAA0000);
    setlinecolor(RED);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    int left = 80;
    int right = 150;
    int top = 150;
    int bottom = 275;
    double strangle = 4 * PI / 3;
    double endangle = 5 * PI / 3;
    solidpie(left, top, right, bottom, strangle, endangle);  // 绘制扇形，表示瞳孔
    Sleep(1000);
    //_getch();  // 等待用户按任意键退出S
    closegraph();  // 关闭图形窗口
    //return 0;
}
void logo4() {
    initgraph(400, 400);  // 创建一个400x400的窗口，对应40x40的方格纸

    // 绘制方格
    for (int i = 0; i <= 400; i += 10) {
        line(0, i, 400, i);  // 横线
        line(i, 0, i, 400);  // 竖线
    }

    // 绘制笑脸

    setfillcolor(0x0055AA);  // 设置填充颜色为黄色
    setlinecolor(RED);   // 设置线条颜色为黑色
    int x;
    int y;
    int xradius;
    int yradius;

    // 绘制圆脸
    x = 50, y = 50, xradius = 350, yradius = 350;
    fillellipse(x, y, xradius, yradius);

    // 绘制眼睛
    setfillcolor(RED);  // 设置填充颜色为白色
    x = 75, y = 150, xradius = 175, yradius = 225;
    fillrectangle(x, y, xradius, yradius);  // 左眼
    x = 225, y = 150, xradius = 325, yradius = 225;
    fillrectangle(x, y, xradius, yradius);  // 右眼
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 10);

    // 绘制瞳孔
    setfillcolor(0x5555FF);
    setlinecolor(0x5555FF);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    int left = 100;
    int right = 150;
    int top = 100;
    int bottom = 225;
    double strangle = 4 * PI / 3;
    double endangle = 5 * PI / 3;
    solidpie(left, top, right, bottom, strangle, endangle); // 绘制扇形，表示瞳孔
    left = 250;
    right = 300;
    solidpie(left, top, right, bottom, strangle, endangle);
    // 绘制鼻子
    setlinecolor(RED);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    left = 140;
    right = 210;
    top = 175;
    bottom = 280;
    strangle = 200;
    endangle = 359;
    arc(left, top, right, bottom, strangle, endangle);  // 绘制弧线，表示鼻子
    Sleep(1000);
    //_getch();  // 等待用户按任意键退出S
    closegraph();  // 关闭图形窗口
    //return 0;
}
void logo5() {
    initgraph(400, 400);  // 创建一个400x400的窗口，对应40x40的方格纸

    // 绘制方格
    for (int i = 0; i <= 400; i += 10) {
        line(0, i, 400, i);  // 横线
        line(i, 0, i, 400);  // 竖线
    }

    // 绘制笑脸

    setfillcolor(0x55FFFF);  // 设置填充颜色为黄色
    setlinecolor(RED);   // 设置线条颜色为黑色
    int x;
    int y;
    int xradius;
    int yradius;

    // 绘制圆脸
    x = 50, y = 50, xradius = 350, yradius = 350;
    fillellipse(x, y, xradius, yradius);

    // 绘制眼睛
    setfillcolor(0xFF55FF);  // 设置填充颜色为白色
    x = 75, y = 150, xradius = 175, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 左眼
    x = 225, y = 150, xradius = 325, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 右眼
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 10);

    // 绘制瞳孔
    setfillcolor(0x5555FF);
    setlinecolor(0x5555FF);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    int left = 100;
    int right = 150;
    int top = 100;
    int bottom = 225;
    double strangle = 4 * PI / 3;
    double endangle = 5 * PI / 3;
    solidpie(left, top, right, bottom, strangle, endangle); // 绘制扇形，表示瞳孔
    left = 250;
    right = 300;
    solidpie(left, top, right, bottom, strangle, endangle);
    Sleep(1000);
    //_getch();  // 等待用户按任意键退出S
    closegraph();  // 关闭图形窗口
    //return 0;
}
void logo6() {
    initgraph(400, 400);  // 创建一个400x400的窗口，对应40x40的方格纸

    // 绘制方格
    for (int i = 0; i <= 400; i += 10) {
        line(0, i, 400, i);  // 横线
        line(i, 0, i, 400);  // 竖线
    }

    // 绘制笑脸

    setfillcolor(0xAAAA00);  // 设置填充颜色为黄色
    setlinecolor(RED);   // 设置线条颜色为黑色
    int x;
    int y;
    int xradius;
    int yradius;

    // 绘制圆脸
    x = 50, y = 50, xradius = 350, yradius = 350;
    fillellipse(x, y, xradius, yradius);

    // 绘制眼睛
    setfillcolor(0xFF55FF);  // 设置填充颜色为白色
    x = 75, y = 150, xradius = 175, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 左眼
    x = 225, y = 150, xradius = 325, yradius = 225;
    fillellipse(x, y, xradius, yradius);  // 右眼
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 10);

    // 绘制瞳孔
    setfillcolor(0x5555FF);
    setlinecolor(0x5555FF);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    int left = 100;
    int right = 150;
    int top = 100;
    int bottom = 225;
    double strangle = 4 * PI / 3;
    double endangle = 5 * PI / 3;
    solidpie(left, top, right, bottom, strangle, endangle); // 绘制扇形，表示瞳孔
    left = 250;
    right = 300;
    solidpie(left, top, right, bottom, strangle, endangle);
    setlinecolor(BROWN);  // 设置线条颜色为红色
    setlinestyle(PS_SOLID, 10);  // 设置线条样式为实线，粗细为5
    left = 100;
    right = 250;
    top = 15;
    bottom = 300;
    strangle = 7 * PI / 6;
    endangle = 11 * PI / 6;
    arc(left, top, right, bottom, strangle, endangle);  // 绘制弧线，表示嘴巴
    Sleep(1000);
    // _getch();  // 等待用户按任意键退出S
    closegraph();  // 关闭图形窗口
    // return 0;
}
