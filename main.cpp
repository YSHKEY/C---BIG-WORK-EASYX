#include <iostream>
#include "include/easyx.h"
#include "include/graphics.h"
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "game.h"
#include "button.h"

void drawText() {
	settextstyle(24, 0, "宋体");//设置文字规格
	settextcolor(BLACK);//设置文字颜色
	setbkmode(TRANSPARENT);//设置背景模式
	outtextxy(250, 250, "left right to move,up to jump,down to flash");//绘制文字
}

ExMessage msg = { 0 };// 定义消息结构体变量

int main() {
	initgraph(1000, 800, EX_SHOWCONSOLE | EX_DBLCLKS);//创建图形窗口
	setbkcolor(RGB(255, 204, 170));//设置窗口背景颜色
	cleardevice();//应用填充颜色

	IMAGE img1;	//定义图片变量
	loadimage(&img1, "assets/background.png", 1000, 800);//加载图片
	putimage(0, 0, &img1);//输出图片

	//播放音乐 m-media c-control i-interface
	mciSendString("open assets/background.mp3 alias bgm1", NULL, 0, NULL);
	mciSendString("play bgm1", NULL, 0, NULL);
	//音量范围是[0,1000]
	MCIERROR ret = mciSendString("setaudio bgm1 volume to 100", NULL, 0, NULL);//音量设置

	//双缓冲绘图
	while (true) {
		BeginBatchDraw();
		cleardevice();
		putimage(0, 0, &img1);

		drawText();

		//捕获输入
		if (peekmessage(&msg, EX_MOUSE | EX_KEY)) {
			switch (msg.message) {
			case(WM_LBUTTONDOWN)://左键按下
				printf("鼠标左键按下 pos(%d,%d)\n", msg.x, msg.y);
				break;
			case(WM_MOUSEMOVE)://鼠标移动
				break;
			}
		}
		if (button(200, 300, 150, 40, "Start")) {
			printf("Start");
			mciSendString("open assets/button.mp3 alias bgmbutton", NULL, 0, NULL);
			mciSendString("play bgmbutton", NULL, 0, NULL);
			Sleep(300);
			gameLoop();
		}
		if (button(650, 300, 150, 40, "End")) {
			printf("End");
			mciSendString("open assets/button.mp3 alias bgmbutton", NULL, 0, NULL);
			mciSendString("play bgmbutton", NULL, 0, NULL);
			Sleep(300);
			return 0;
		}
		EndBatchDraw();
		msg.message = 0;
	}

	getchar();
	return 0;
}

