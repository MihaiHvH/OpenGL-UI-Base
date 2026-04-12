#pragma once

#include "../../main.hpp"

class pGraphics::pButton : public pGraphics::pElement {
    private:
        int state = 0;
        std::vector<pColor> colors;
        void(*function)(int);

    public:
        pButton(pGraphics* gfx, std::pair<double, double> pos, std::pair<double, double> size, std::vector<pColor> colors, void(*function)(int));
        ~pButton();

        void draw();
        void checkClick();
        
        void setPos(std::pair<double, double> newPos) { this->pos = newPos; };
        void setSize(std::pair<double, double> newSize) { this->size = newSize; };
        void setColors(std::vector<pColor> newColors);
        void setFunction(void(*newFunction)(int)) { function = newFunction; };
        void setState(int newState);
        
        std::pair<double, double> getPos() { return this->pos; };
        std::pair<double, double> getSize() { return this->size; };
        std::vector<pColor> getColors() { return colors; };
        int getState() { return state; };
};