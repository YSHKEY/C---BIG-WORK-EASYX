#include <iostream>
#include "game.h"
#include "button.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern ExMessage msg;

void showGameOverScreen() {
    // 停止背景音乐
    mciSendString("close bgm1", NULL, 0, NULL); // 假设背景音乐的别名是 "bgm"

    // 播放游戏结束音效
    mciSendString("open assets/gameover.mp3 alias end", NULL, 0, NULL);
    mciSendString("play end", NULL, 0, NULL);

    // 显示 "Game Over" 文本
    cleardevice(); // 清除屏幕内容
    settextstyle(30, 0, "宋体");
    settextcolor(RED);
    outtextxy(400, 300, "Game Over"); // 显示 "Game Over" 文本
    outtextxy(320, 350, "Press any key to exit..."); // 提示用户按键退出

    Sleep(2500);

    // 等待用户按下任意键
    ExMessage msg1;
    while (true) {
        if (peekmessage(&msg1, EM_KEY)) { // 检测键盘事件
            if (msg1.message == WM_KEYDOWN) { // 如果按下任意键
                break; // 退出循环
            }
        }
        Sleep(50); // 减少 CPU 占用
    }

    // 直接退出程序
    exit(0);
}

void gameLoop() {
    // 加载地图资源
    IMAGE maps[4];
    loadimage(&maps[0], "assets/map1.png", 1000, 800);
    loadimage(&maps[1], "assets/map2.png", 1000, 800);
    loadimage(&maps[2], "assets/map3.png", 1000, 800);
    loadimage(&maps[3], "assets/map4.png", 1000, 800);

    Player player;
    int currentMap = 0; // 当前地图编号（从 0 开始）

    while (true) {
        BeginBatchDraw(); // 开始双缓冲绘图
        cleardevice();    // 清除屏幕内容

        // 绘制当前地图
        putimage(0, 0, &maps[currentMap]);

        // 动态调整地面高度
        player.updateGroundY(currentMap);

        // 绘制角色
        player.draw();

        // 捕获键盘输入
        if (peekmessage(&msg, EX_KEY)) {
            switch (msg.message) {
            case WM_KEYDOWN:
                player.handleInput(true, msg.vkcode);
                break;
            case WM_KEYUP:
                player.handleInput(false, msg.vkcode);
                break;
            }
        }

        // 更新角色状态并检测是否死亡
        if (player.update(currentMap)) {
            EndBatchDraw(); // 确保当前帧绘制完成
            playDeathAnimation(player.getX(), player.getY()); // 播放死亡动画
            showGameOverScreen(); // 显示 "Game Over" 文本
            break; // 退出游戏循环
        }

        // 检测地图切换
        if (player.getX() > 950) { // 当角色到达地图右侧
            currentMap = (currentMap + 1) % 4; // 循环切换地图
            player.setPosition(0, player.getY()); // 重置角色位置到地图左侧
            player.resetState();                  // 重置角色状态
        }

        EndBatchDraw(); // 结束双缓冲绘图
        Sleep(10);      // 控制帧率
    }
}

void playDeathAnimation(int x, int y) {
    // 加载死亡动画资源
    IMAGE reddie1, reddie2, reddie3;
    loadimage(&reddie1, "assets/reddie1.png", 50, 50);
    loadimage(&reddie2, "assets/reddie2.png", 50, 50);
    loadimage(&reddie3, "assets/reddie3.png", 50, 50);

    // 播放死亡动画
    for (int i = 0; i < 3; i++) {
        cleardevice(); // 清除屏幕内容
        switch (i) {
        case 0:
            putimage(x, y, &reddie1, NOTSRCERASE);
            putimage(x, y, &reddie1, SRCINVERT);
            break;
        case 1:
            putimage(x, y, &reddie2, NOTSRCERASE);
            putimage(x, y, &reddie2, SRCINVERT);
            break;
        case 2:
            putimage(x, y, &reddie3, NOTSRCERASE);
            putimage(x, y, &reddie3, SRCINVERT);
            break;
        }
        Sleep(300); // 每帧停留 300 毫秒
    }
}