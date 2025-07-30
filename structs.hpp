#pragma once

#include <utility>
#include <string>

struct pColor {
    int r;
    int g;
    int b;
    int a;
};

struct pScreen {
    std::string windowName = "OpenGL-UI-Base";
    std::pair<int, int> size = { 640, 640 };
    std::pair<int, int> initialSize = { 640, 640 };
    std::pair<int, int> mousePointer;
    bool leftClick = false;
    bool rightClick = false;
    bool leftClickDrag = false;

    void(*render)(void) = nullptr;
};

extern pScreen screen;