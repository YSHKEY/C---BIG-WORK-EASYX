#include "player.h"
#include <iostream>

Player::Player()
    : x(100), y(500), dx(0), dy(0), gravity(1), groundY(500), jumpSpeed(-18), dashSpeed(15), dashTime(10), isDashing(false), canDash(true), dashTimer(0), currentState(0) {
        loadimage(&red_, "assets/red_.png", 50, 50);
        loadimage(&red, "assets/red.png", 50, 50);
        loadimage(&redleft_, "assets/redleft_.png", 50, 50);
        loadimage(&redleft, "assets/redleft.png", 50, 50);
        loadimage(&redright_, "assets/redright_.png", 50, 50);
        loadimage(&redright, "assets/redright.png", 50, 50);
        loadimage(&redleftup_, "assets/redleftup_.png", 50, 50);
        loadimage(&redleftup, "assets/redleftup.png", 50, 50);
        loadimage(&redrightup_, "assets/redrightup_.png", 50, 50);
        loadimage(&redrightup, "assets/redrightup.png", 50, 50);
        loadimage(&redrunleft_, "assets/redrunleft_.png", 50, 50);
        loadimage(&redrunleft, "assets/redrunleft.png", 50, 50);
        loadimage(&redrunright_, "assets/redrunright_.png", 50, 50);
        loadimage(&redrunright, "assets/redrunright.png", 50, 50);
    }

    void Player::setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }
    
    void Player::resetState() {
        dx = 0;
        dy = 0;
        isDashing = false;
        canDash = true;
        dashTimer = 0;
        currentState = 0;
    }

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
                if (!isDashing) { // 冲刺过程中不改变状态
                    dx = -7;
                    currentState = (y < groundY) ? 3 : 1;
                }
                break;
            case VK_RIGHT:
                if (!isDashing) { // 冲刺过程中不改变状态
                    dx = 7;
                    currentState = (y < groundY) ? 4 : 2;
                }
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
                    currentState = (y < groundY) ? 0 : currentState;
                }
                break;
            }
        }
    }

    bool Player::update(int currentMap) {
        if (isDashing) {
            // 冲刺逻辑
            x += dx;
            dashTimer--;
            if (dashTimer <= 0) {
                isDashing = false; // 冲刺结束
    
                // 检查当前是否有方向键被按下
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    dx = -5; // 继续向左移动
                    currentState = 1; // 左移动状态
                } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    dx = 5; // 继续向右移动
                    currentState = 2; // 右移动状态
                } else {
                    dx = 0; // 停止移动
                    currentState = 0; // 静止状态
                }
            }
        } else {
            // 正常移动逻辑
            dy += gravity;
            x += dx;
            y += dy;
    
            // 根据水平速度调整状态
            if (y == groundY) {
                currentState = (dx < 0) ? 1 : (dx > 0) ? 2 : 0;
            }
        }
    
        if (y >= groundY) {
            y = groundY;
            dy = 0;
            canDash = true; // 落地后重置冲刺能力
        }

        // 编写墙体功能
        if (currentMap == 0) {
        }

        if (currentMap == 1) {
            if(groundY == 800 && y > 500){
                if(x < 530)x = 530;
                if(x > 610)x = 610;
            }
        }

        if (currentMap == 2) {
            if(groundY == 800 && y > 500){
                if(x < 530)x = 530;
                if(x > 735)x = 735;
            }
        }

        if (currentMap == 3) {
            if(groundY == 500 && y > 410){
                if(x > 155)x = 155;
            }
            if(groundY == 460 && y > 360){
                if(x < 735)x = 735;
            }
            if(groundY == 800){
                if(y > 410 && x < 345)x = 345;
                if(y > 360 && x > 545)x = 545;
            }
        }

        if (currentMap == 4) {
            if(groundY == 500 && x < 500 && y > 390){
                if(x > 300)x = 300;
            }
            if(groundY == 390 && x < 500 && y > 300){
                if(x > 385)x = 385;
            }
            if(groundY == 390 && x > 500 && y > 300){
                if(x < 565)x = 565;
            }
            if(groundY == 500 && x > 500 && y > 390){
                if(x < 650)x = 650;
            }
        }
    
        if (currentMap == 5) {
            if(groundY == 500 && y > 390){
                if(x > 445)x = 445;
            }
            if(groundY == 390 && y > 285){
                if(x > 670)x = 670;
            }
        }

        if (currentMap == 6) {
        }

        else if (currentMap == 7) {
            if(groundY == 800 && x < 360 && y > 500){
                if(x < 185)x = 185;
                if(x > 240)x = 240;
            }
            if(groundY == 800 && x > 360 && y > 500){
                if(x < 440)x = 440;
                if(x > 505)x = 505;
            }
        }

        if (currentMap == 8) {
            if(groundY == 800 && x < 500){
                if(y > 500 && x < 270)x = 270;
                if(y > 395 && x > 375)x = 375;
            }
            if(groundY == 800 && x > 500){
                if(y > 395 && x < 570)x = 570;
                if(y > 500 && x > 735)x = 735;
            }
        }

        if (currentMap == 9) {
            if(groundY == 800 && x < 630){
                if(y > 105 && x < 170)x = 170;
                if(y > 600 && x < 500)x = 500;
            }
            if(groundY == 800 && x > 630){
                if(y > 600 && x < 710)x = 570;
                if(y > 600 && x > 840)x = 840;
            }
        }

        if (x < 0) x = 0; // 防止角色超出左边界
    
        // 检测是否掉落到底部
        if (y >= 800) { // 窗口底部为死亡区域
            return true; // 返回 true 表示角色死亡
        }
    
        return false; // 返回 false 表示角色未死亡
    }

    void Player::updateGroundY(int currentMap) {
        if (currentMap == 0) {
            groundY = 500;
        }
        else if (currentMap == 1) {
            groundY = (x > 525 && x < 615) ? 800 : 500;
        }
        else if (currentMap == 2) {
            groundY = (x > 525 && x < 740) ? 800 : 500;
        }
        else if (currentMap == 3) {
            if(x > 160 && x <= 340) groundY = 410;
            else if(x > 340 && x <= 550) groundY = 800;
            else if(x > 550 && x <= 730) groundY = 360;
            else if(x > 730) groundY = 460;
            else { groundY = 500; }
        }
        else if (currentMap == 4) {
            if(x > 305 && x <= 390) groundY = 390;
            else if(x > 390 && x <= 560) groundY = 300;
            else if(x > 560 && x <= 645) groundY = 390;
            else { groundY = 500; }
        }
        else if (currentMap == 5) {
            if(x > 450 && x <= 675) groundY = 390;
            else if(x > 675) groundY = 285;
            else { groundY = 500; }
        }
        else if (currentMap == 6) {
            groundY = 500;
        }
        else if (currentMap == 7) {
            if(x <= 180) groundY = 500;
            else if(x > 180 && x <= 245) groundY = 800;
            else if(x > 245 && x <= 440) groundY = 500;
            else if(x > 440 && x <= 510) groundY = 800;
            else { groundY = 500; }
        }
        else if (currentMap == 8) {
            if(x > 265 && x <= 380) groundY = 800;
            else if(x > 380 && x <= 565) groundY = 395;
            else if(x > 565 && x <= 740) groundY = 800;
            else { groundY = 500; }
        }
        else if (currentMap == 9) {
            if(x <= 165) groundY = 105;
            else if(x > 165 && x <= 505) groundY = 800;
            else if(x > 705 && x <= 845) groundY = 800;
            else { groundY = 600; }
        }
        else if (currentMap == 10) {
            groundY = 605;
        }
        fflush(stdout);
    }
    
    void Player::draw() {
        switch (currentState) {
        case 0:
            putimage(x, y, &red_, NOTSRCERASE);
            putimage(x, y, &red, SRCINVERT);
            break;
        case 1:
            putimage(x, y, &redleft_, NOTSRCERASE);
            putimage(x, y, &redleft, SRCINVERT);
            break;
        case 2:
            putimage(x, y, &redright_, NOTSRCERASE);
            putimage(x, y, &redright, SRCINVERT);
            break;
        case 3:
            putimage(x, y, &redleftup_, NOTSRCERASE);
            putimage(x, y, &redleftup, SRCINVERT);
            break;
        case 4:
            putimage(x, y, &redrightup_, NOTSRCERASE);
            putimage(x, y, &redrightup, SRCINVERT);
            break;
        case 5:
            putimage(x, y, &redrunleft_, NOTSRCERASE);
            putimage(x, y, &redrunleft, SRCINVERT);
            break;
        case 6:
            putimage(x, y, &redrunright_, NOTSRCERASE);
            putimage(x, y, &redrunright, SRCINVERT);
            break;
        }
    }