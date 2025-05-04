#include "player.h"

Player::Player()
    : x(100), y(550), dx(0), dy(0), gravity(1), groundY(550), jumpSpeed(-20), dashSpeed(15), dashTime(10), isDashing(false), canDash(true), dashTimer(0), currentState(0) {}

    void Player::handleInput(bool keyDown, int key) {
        if (keyDown) {
            switch (key) {
            case VK_UP:
                if (y == groundY) {
                    dy = jumpSpeed;
                    currentState = (dx < 0) ? 3 : (dx > 0) ? 4 : 0;
                }
                break;
            case VK_LEFT:
                dx = -5;
                currentState = (y < groundY) ? 3 : 1;
                break;
            case VK_RIGHT:
                dx = 5;
                currentState = (y < groundY) ? 4 : 2;
                break;
            case VK_DOWN:
                if (canDash) { // 只有在可以冲刺时才能触发
                    isDashing = true;
                    dashTimer = dashTime; // 设置冲刺持续时间
                    if (dx < 0) {
                        dx = -dashSpeed; // 向左冲刺
                        currentState = 5; // 冲刺状态
                    } else if (dx > 0) {
                        dx = dashSpeed; // 向右冲刺
                        currentState = 6; // 冲刺状态
                    }
                    canDash = false; // 冲刺后禁用冲刺
                }
                break;
            }
        }
        else {
            switch (key) {
            case VK_LEFT:
            case VK_RIGHT:
                if (!isDashing) { // 只有在非冲刺状态下停止移动
                    dx = 0;
                    currentState = (y < groundY) ? currentState : 0;
                }
                break;
            }
        }
    }

    bool Player::update() {
        if (isDashing) {
            // 冲刺逻辑
            x += dx;
            dashTimer--;
            if (dashTimer <= 0) {
                isDashing = false; // 冲刺结束
                dx = 0;            // 停止水平移动
                currentState = 0;  // 恢复默认状态
            }
        } else {
            // 正常移动逻辑
            dy += gravity;
            x += dx;
            y += dy;
        }
    
        if (y >= groundY) {
            y = groundY;
            dy = 0;
            currentState = (dx < 0) ? 1 : (dx > 0) ? 2 : 0;
            canDash = true; // 落地后重置冲刺能力
        }
    
        if (x < 0) x = 0;
        if (x > 950) x = 950;
    
        // 检测是否掉落到底部
        if (y >= 750) {
            return true; // 返回 true 表示角色死亡
        }
    
        return false; // 返回 false 表示角色未死亡
    }
    
    void Player::draw() {
        switch (currentState) {
        case 0:
            loadimage(&red_, "assets/red_.png", 50, 50);
            loadimage(&red, "assets/red.png", 50, 50);
            putimage(x, y, &red_, NOTSRCERASE);
            putimage(x, y, &red, SRCINVERT);
            break;
        case 1:
            loadimage(&redleft_, "assets/redleft_.png", 50, 50);
            loadimage(&redleft, "assets/redleft.png", 50, 50);
            putimage(x, y, &redleft_, NOTSRCERASE);
            putimage(x, y, &redleft, SRCINVERT);
            break;
        case 2:
            loadimage(&redright_, "assets/redright_.png", 50, 50);
            loadimage(&redright, "assets/redright.png", 50, 50);
            putimage(x, y, &redright_, NOTSRCERASE);
            putimage(x, y, &redright, SRCINVERT);
            break;
        case 3:
            loadimage(&redleftup_, "assets/redleftup_.png", 50, 50);
            loadimage(&redleftup, "assets/redleftup.png", 50, 50);
            putimage(x, y, &redleftup_, NOTSRCERASE);
            putimage(x, y, &redleftup, SRCINVERT);
            break;
        case 4:
            loadimage(&redrightup_, "assets/redrightup_.png", 50, 50);
            loadimage(&redrightup, "assets/redrightup.png", 50, 50);
            putimage(x, y, &redrightup_, NOTSRCERASE);
            putimage(x, y, &redrightup, SRCINVERT);
            break;
        case 5:
            loadimage(&redrunleft_, "assets/redrunleft_.png", 50, 50);
            loadimage(&redrunleft, "assets/redrunleft.png", 50, 50);
            putimage(x, y, &redrunleft_, NOTSRCERASE);
            putimage(x, y, &redrunleft, SRCINVERT);
            break;
        case 6:
            loadimage(&redrunright_, "assets/redrunright_.png", 50, 50);
            loadimage(&redrunright, "assets/redrunright.png", 50, 50);
            putimage(x, y, &redrunright_, NOTSRCERASE);
            putimage(x, y, &redrunright, SRCINVERT);
            break;
        }
    }