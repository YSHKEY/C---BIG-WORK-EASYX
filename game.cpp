#include <iostream>
#include "game.h"
#include "button.h"

extern ExMessage msg;

void gameLoop() {
    IMAGE map1;
    loadimage(&map1, "assets/map1.png", 1000, 200);

    Player player;

    while (true) {
        BeginBatchDraw();
        setbkcolor(RGB(255, 204, 170));
        cleardevice();
        putimage(0, 600, &map1);

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

        // 更新玩家状态并检测是否死亡
        if (player.update()) {
            playDeathAnimation(player.getX(), player.getY());
            break; // 退出游戏循环
        }

        player.draw();

        EndBatchDraw();
        Sleep(10);
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