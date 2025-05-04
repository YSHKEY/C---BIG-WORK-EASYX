#include "button.h"

extern ExMessage msg;

bool inArea(int mx, int my, int x, int y, int w, int h) {
    return mx > x && mx < x + w && my > y && my < y + h;
}

bool button(int x, int y, int w, int h, const char* text) {
    if (inArea(msg.x, msg.y, x, y, w, h)) {
        setfillcolor(RGB(50, 129, 142));
        settextcolor(RGB(0, 0, 0));
    } else {
        setfillcolor(RGB(73, 189, 186));
        settextcolor(RGB(37, 41, 40));
    }
    fillroundrect(x, y, x + w, y + h, 5, 5);
    int wSpace = (w - textwidth(text)) / 2;
    int hSpace = (h - textheight(text)) / 2;
    setbkmode(TRANSPARENT);
    outtextxy(x + wSpace, y + hSpace, text);

    if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h)) {
        return true;
    }
    return false;
}