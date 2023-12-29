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
    
    void draw4PointRect(std::pair<int, int> point[4], pColor color);
    void drawSquare(std::pair<int, int> pos, std::pair<int, int> size, pColor color);
    void drawFilledCircle(std::pair<int, int> centrePos, double r, pColor color);
    std::pair<int, int> getTextSize(const char* str, void* font);
    void drawText(std::pair<int, int> pos, void *font, const char* str, pColor color);
    void drawTriangle(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, pColor color);
    bool mouseInRegion(std::pair<int, int> mousePointer, std::pair<int, int> pos, std::pair<int, int> size);

    pColor createNewColor(int r, int g, int b, int a = 255);
};