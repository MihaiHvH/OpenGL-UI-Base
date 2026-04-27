#pragma once

struct pScreen {
    std::pair<double, double> mousePointer;
    bool leftClick = false;
    bool rightClick = false;
};

extern pScreen screen;