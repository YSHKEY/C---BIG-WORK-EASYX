#ifndef BUTTON_H
#define BUTTON_H

#include "include/easyx.h"
#include "include/graphics.h"

bool inArea(int mx, int my, int x, int y, int w, int h);
bool button(int x, int y, int w, int h, const char* text);

#endif // BUTTON_H