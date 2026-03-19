#pragma once

#include "../../main.hpp"

class pGraphics::pButton : public pGraphics {
    private:
    int state = 0;

    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::vector<pColor> colors;
    void(*function)(int);
    
    pGraphics::pText *textObj;

    public:
    pButton(std::pair<double, double> pos, std::pair<double, double> size, std::vector<pColor> colors, std::string fontLocation, int fontSize, pColor textColor, std::string text, void(*function)(int));
    ~pButton();

    void init();
    void draw();
    void checkClick();
    
    void setPos(std::pair<double, double> newPos) { pos = newPos; };
    void setSize(std::pair<double, double> newSize) { size = newSize; };
    void setColors(std::vector<pColor> newColors);
    void setFunction(void(*newFunction)(int)) { function = newFunction; };
    void setState(int newState);
    
    std::pair<double, double> getPos() { return pos; };
    std::pair<double, double> getSize() { return size; };
    int getState() {return state; };
    pGraphics::pText *getTextObj() { return textObj; };
};