#pragma once

#include "../../main.hpp"

class pGraphics::pCheckBox : public pGraphics {
    private:
    int state = 0;
    
    std::pair<double, double> pos;
    std::pair<double, double> size;
    bool textOrientation;
    pColor outlineColor;
    std::vector<pColor> colors;
    void(*function)(int);
    pGraphics::pText *textObj;

    public:
    pCheckBox(std::pair<double, double> pos, std::pair<double, double> size, std::string fontLocation, int fontSize, std::string text, bool textOrientation, pColor textColor, pColor outlineColor, std::vector<pColor> colors, void(*function)(int));
    ~pCheckBox();

    void init();

    void checkClick();
    void draw();

    void setPos(std::pair<double, double> newPos) { pos = newPos; };
    void setSize(std::pair<double, double> newSize) { size = newSize; };
    void setTextOrientation(bool newTextOrientation) { textOrientation = newTextOrientation; };
    void setOutlineColor(pColor newOutlineColor) { outlineColor = newOutlineColor; };
    void setColors(std::vector<pColor> newColors);
    void setFunction(void(*newFunction)(int)) { function = newFunction; };
    void setState(int newState);

    std::pair<double, double> getPos() { return pos; };
    std::pair<double, double> getSize() { return size; };
    int getState() { return state; };
    pGraphics::pText* getTextObj() { return textObj; };
};