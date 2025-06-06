#include <iostream>
#include "game.h"
#include "button.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern ExMessage msg;

void showGameOverScreen() {
    // 停止背景音乐
    mciSendString("close bgm1", NULL, 0, NULL);

    // 播放游戏结束音效
    mciSendString("open assets/gameover.mp3 alias badend", NULL, 0, NULL);
    mciSendString("play badend", NULL, 0, NULL);

    // 显示 "Game Over" 文本
    cleardevice();
    settextstyle(30, 0, "宋体");
    settextcolor(RED);
    outtextxy(400, 300, "Game Over");
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
        Sleep(50);
    }

    // 直接退出程序
    exit(0);
}

void gameLoop() {
    // 加载地图资源
    IMAGE maps[11];
    loadimage(&maps[0], "assets/map1.png", 1000, 800);
    loadimage(&maps[1], "assets/map2.png", 1000, 800);
    loadimage(&maps[2], "assets/map3.png", 1000, 800);
    loadimage(&maps[3], "assets/map4.png", 1000, 800);
    loadimage(&maps[4], "assets/map5.png", 1000, 800);
    loadimage(&maps[5], "assets/map6.png", 1000, 800);
    loadimage(&maps[6], "assets/map7.png", 1000, 800);
    loadimage(&maps[7], "assets/map8.png", 1000, 800);
    loadimage(&maps[8], "assets/map9.png", 1000, 800);
    loadimage(&maps[9], "assets/map10.png", 1000, 800);
    loadimage(&maps[10], "assets/map11.png", 1000, 800);

    Player player;
    int currentMap = 0; // 当前地图编号（从 0 开始）

    while (true) {
        BeginBatchDraw(); // 开始双缓冲绘图
        cleardevice();

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
            EndBatchDraw();
            showGameOverScreen(); // 显示 "Game Over" 文本
            break; // 退出游戏循环
        }

        // 检测地图切换
        if (player.getX() > 950) { // 当角色到达地图右侧
            currentMap += 1; // 切换地图
            if (currentMap == 9) player.setPosition(0, 105);
            else{ player.setPosition(0, player.getY()); } // 重置角色位置到地图左侧
            player.resetState(); // 重置角色状态
        }

        // 游戏胜利结束
        if (currentMap == 10) {
            if(player.getX() >= 890 && player.getY() >= 540){
                EndBatchDraw();
                victory();
                break;
            }
        }

        EndBatchDraw(); // 结束双缓冲绘图
        Sleep(10);      // 控制帧率
    }
}

void victory(){
    // 停止背景音乐
    mciSendString("close bgm1", NULL, 0, NULL);

    // 播放游戏胜利结束音效
    mciSendString("open assets/victory.mp3 alias goodend", NULL, 0, NULL);
    mciSendString("play goodend", NULL, 0, NULL);

    // 显示 "Victory" 文本
    cleardevice();
    settextstyle(30, 0, "宋体");
    settextcolor(RED);
    outtextxy(400, 300, "Victory");
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
        Sleep(50);
    }

    // 直接退出程序
    exit(0);
}