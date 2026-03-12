#pragma once

#include "../../main.hpp"

class pGraphics::pSlider : public pGraphics {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::pair<double, double> minMax;
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
    pSlider(std::pair<double, double> pPos, std::pair<double, double> pSize, std::pair<double, double> pMinMax, int pPrecision, bool pReal, void *pFont, bool pTextPos, std::string pText, pColor pOnColor, pColor pOffColor, pColor pOutlineColor, pColor pValueTextColor, pColor pTextColor, void(*onValueChange)(double));
    ~pSlider();

    void draw();
    void handleMouse();

    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setMinMax(std::pair<double, double> newMinMax);
    void setPrecision(int newPrecision);
    void setReal(bool newReal);
    void setFont(void *newFont);
    void setTextPos(bool newTextPos);
    void setText(std::string newText);
    void setOnColor(pColor newOnColor);
    void setOffColor(pColor newOffColor);
    void setOutlineColor(pColor newOutlineColor);
    void setValueTextColor(pColor newValueTextColor);
    void setTextColor(pColor newTextColor);
    void setFunction(void(*newOnValueChange)(double));
    void setValue(double newValue);
    double getValue();
};