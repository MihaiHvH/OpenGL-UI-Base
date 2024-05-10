#pragma once

#include <utility>
#include "../structs.hpp"

class pGraphics {
    private:

    public:
    pGraphics();
    ~pGraphics();
    
    class pButon;
    class pTextBox;
    class pCheckBox;
    class pImage;
    class pSlider;

    pColor white, black, red, green, blue, yellow, cyan, purple;
    
    void draw4PointRect(std::pair<double, double> point[4], pColor color);
    void drawRect(std::pair<double, double> pos, std::pair<double, double> size, pColor color);
    void drawFilledCircle(std::pair<double, double> centrePos, double r, pColor color);
    std::pair<int, int> getTextSize(const char* str, void* font);
    void drawText(std::pair<double, double> pos, void *font, const char* str, pColor color);
    void drawTriangle(std::pair<double, double> point[3], pColor color);
    bool mouseInRegion(std::pair<int, int> mousePointer, std::pair<double, double> pos, std::pair<double, double> size);

    pColor createNewColor(int r, int g, int b, int a = 255);
};