#pragma once

#include <utility>

class pGraphics {
    public:
    pGraphics();
    ~pGraphics();

    void(*render)(void);
    
    class pButon;
    class pTextBox;
    class pCheckBox;
    class pImage;
    class pSlider;

    pColor white, black, red, green, blue, yellow, cyan, purple;
    
    void draw4PointRect(std::pair<double, double> points[4], pColor color);
    void drawRect(std::pair<double, double> pos, std::pair<double, double> size, pColor color);
    void drawFilledCircle(std::pair<double, double> centrePos, double r, pColor color);
    void drawOutlinedCircle(std::pair<double, double> centrePos, double r, double lineThickness, pColor color);
    void drawFilledEllipse(std::pair<double, double> pos, std::pair<double, double> size, pColor color);
    void drawOutlinedEllipse(std::pair<double, double> pos, std::pair<double, double> size, double lineThickness, pColor color);
    std::pair<int, int> getTextSize(const char* str, void* font);
    void drawText(std::pair<double, double> pos, void *font, const char* str, pColor color);
    void drawTriangle(std::pair<double, double> points[3], pColor color);
    bool mouseInRegion(std::pair<double, double> pos, std::pair<double, double> size);

    pColor createNewColor(int r, int g, int b, int a = 255);
};