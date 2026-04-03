#pragma once

#include "../../main.hpp"

class pGraphics::pButton : public pGraphics {
    private:
    int state = 0;

    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::vector<pColor> colors;
    void(*function)(int);

    public:
    pButton(std::pair<double, double> pos, std::pair<double, double> size, std::vector<pColor> colors, void(*function)(int));
    ~pButton();

    void draw();
    void checkClick();
    
    void setPos(std::pair<double, double> newPos) { pos = newPos; };
    void setSize(std::pair<double, double> newSize) { size = newSize; };
    void setColors(std::vector<pColor> newColors);
    void setFunction(void(*newFunction)(int)) { function = newFunction; };
    void setState(int newState);
    
    std::pair<double, double> getPos() { return pos; };
    std::pair<double, double> getSize() { return size; };
    int getState() { return state; };
};