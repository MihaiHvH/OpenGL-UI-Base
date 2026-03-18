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
    std::pair<double, double> mousePointer;
    bool leftClick = false;
    bool rightClick = false;

    GLFWwindow *window;
    void(*render)(void) = nullptr;

    mat4 projection, view, model;
};

extern pScreen screen;