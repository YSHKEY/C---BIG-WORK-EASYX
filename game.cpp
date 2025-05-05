#include <iostream>
#include "game.h"
#include "button.h"

extern ExMessage msg;

void gameLoop() {
    // 加载地图资源
    IMAGE maps[3];
    loadimage(&maps[0], "assets/map1.png", 1000, 800);
    loadimage(&maps[1], "assets/map2.png", 1000, 800);
    loadimage(&maps[2], "assets/map3.png", 1000, 800);

    Player player;
    int currentMap = 0; // 当前地图编号（从 0 开始）

    while (true) {
        BeginBatchDraw(); // 开始双缓冲绘图
        cleardevice();    // 清除屏幕内容

        // 绘制当前地图
        putimage(0, 0, &maps[currentMap]);

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
        if (player.update()) {
            playDeathAnimation(player.getX(), player.getY());
            break; // 如果角色死亡，退出游戏循环
        }

        // 检测地图切换
        if (player.getX() > 950) { // 当角色到达地图右侧
            currentMap = (currentMap + 1) % 3; // 循环切换地图
            player.setPosition(0, player.getY()); // 重置角色位置到地图左侧
            player.resetState(); // 重置角色状态

            // 调试输出
            printf("地图切换到: %d\n", currentMap + 1);
        }

        EndBatchDraw(); // 结束双缓冲绘图
        Sleep(10);      // 控制帧率
    }
}

void playDeathAnimation(int x, int y) {
    IMAGE reddie1, reddie2, reddie3;
    loadimage(&reddie1, "assets/reddie1.png", 50, 50);
    loadimage(&reddie2, "assets/reddie2.png", 50, 50);
    loadimage(&reddie3, "assets/reddie3.png", 50, 50);

    cleardevice();
    putimage(x, y, &reddie1, NOTSRCERASE);
    putimage(x, y, &reddie1, SRCINVERT);
    Sleep(300);

    cleardevice();
    putimage(x, y, &reddie2, NOTSRCERASE);
    putimage(x, y, &reddie2, SRCINVERT);
    Sleep(300);

    cleardevice();
    putimage(x, y, &reddie3, NOTSRCERASE);
    putimage(x, y, &reddie3, SRCINVERT);
    Sleep(300);

    cleardevice();
    settextstyle(30, 0, "宋体");
    settextcolor(RED);
    outtextxy(400, 300, "Game Over");
    getchar(); // 等待用户按键
}