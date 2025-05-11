#ifndef PLAYER_H
#define PLAYER_H

#include "include/easyx.h"
#include "include/graphics.h"

class Player {
private:
    int x, y;
    int dx, dy;
    int gravity;
    int groundY;
    const int jumpSpeed;
    const int dashSpeed; // 冲刺速度
    const int dashTime; // 冲刺持续时间（帧数）
    bool isDashing; // 是否正在冲刺
    bool canDash; // 是否可以冲刺
    int dashTimer; // 冲刺计时器

    IMAGE red, redleft, redright, red_, redleft_, redright_;
    IMAGE redleftup, redleftup_, redrightup, redrightup_;
    IMAGE redrunleft, redrunleft_, redrunright, redrunright_;

    int currentState;
public:
    Player();
    void handleInput(bool keyDown, int key);
    bool update(int currentMap);
    void draw();
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newx, int newy);
    void resetState();
    void updateGroundY(int currentMap);
};

#endif // PLAYER_H