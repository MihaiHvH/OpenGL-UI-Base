#pragma once

#include "../../main.hpp"

class pGraphics::pSlider : public pGraphics {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::pair<double, double> minMax;
    int precision;
    bool real;
    int valueTextSize;
    bool textPos;
    pColor onColor;
    pColor offColor;
    pColor outlineColor;
    void(*function)(double value);

    double value;
    double pxOn;
    double pxOff;
    std::string valueText;

    pGraphics::pText* textObj;
    pGraphics::pText* valueTextObj;

    public:
    /*
    if pReal = true than the value of pPrecision doesn't matter
    if pPrecision = -1 than it is the whole number without the ending 0s
    pPrecision shows the number with pPrecision decimals, if the pPrecision's decimal is 0 than it doesn't show the 0
    pTextPos, if false left otherwise right
    */
    pSlider(std::pair<double, double> pos, std::pair<double, double> size, std::pair<double, double> minMax, int precision, bool real, std::string fontLocation, int textSize, int valueTextSize, bool textPos, std::string text, pColor onColor, pColor offColor, pColor outlineColor, pColor valueTextColor, pColor textColor, void(*function)(double));
    ~pSlider();

    void init();
    void draw();
    void handleMouse();

    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setMinMax(std::pair<double, double> newMinMax);
    void setPrecision(int newPrecision);
    void setReal(bool newReal);
    void setTextPos(bool newTextPos) { textPos = newTextPos; };
    void setOnColor(pColor newOnColor) { onColor = newOnColor; };
    void setOffColor(pColor newOffColor) { offColor = newOffColor; };
    void setOutlineColor(pColor newOutlineColor) { outlineColor = newOutlineColor; };
    void setFunction(void(*newFunction)(double)) { function = newFunction; };
    void setValue(double newValue);
    
    std::pair<double, double> getPos() { return pos; };
    std::pair<double, double> getSize() { return size; };
    pGraphics::pText* getValueTextObj() { return valueTextObj; };
    pGraphics::pText* getTextObj() { return textObj; };
    double getValue() { return value; };
};