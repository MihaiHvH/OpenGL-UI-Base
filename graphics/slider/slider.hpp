#pragma once

#include "../../main.hpp"

class pGraphics::pSlider : public pGraphics {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::pair<double, double> min_max;
    int precision;
    bool real;
    void *font;
    bool textPos;
    std::string text;
    pColor onColor;
    pColor offColor;
    pColor outlineColor;
    pColor valueTextColor;
    pColor textColor;
    void(*onValueChange)(double value);

    double value;
    double pxOn;
    double pxOff;
    std::string valueText;

    public:
    /*
    if pReal = true than the value of pPrecision doesn't matter
    if pPrecision = -1 than it is the whole number without the ending 0s
    pPrecision shows the number with pPrecision decimals, if the pPrecision's decimal is 0 than it doesn't show the 0
    pTextPos, if false left otherwise right
    */
    pSlider(std::pair<int, int> pPos, std::pair<int, int> pSize, std::pair<double, double> pMin_max, int pPrecision, bool pReal, void *pFont, bool pTextPos, std::string pText, pColor pOnColor, pColor pOffColor, pColor pOutlineColor, pColor pValueTextColor, pColor pTextColor, void(*onValueChange)(double value));
    ~pSlider();

    void draw();
    void handleMouse();
    void updatePos(std::pair<double, double> pPos);
    void updateSize(std::pair<double, double> pSize);
};