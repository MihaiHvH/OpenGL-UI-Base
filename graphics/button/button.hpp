#pragma once

#include "../../main.hpp"

class pGraphics::pButton : public pGraphics::pElement {
    private:
        int state = 0;
        std::vector<pColor> colors;
        void(*function)(int);

    public:
        pButton(pGraphics* gfx, std::pair<float, float> pos, std::pair<float, float> size, std::vector<pColor> colors, void(*function)(int));
        ~pButton();

        void draw();
        void checkClick();
        
        void setPos(std::pair<float, float> newPos) { pos = newPos; };
        void setSize(std::pair<float, float> newSize) { size = newSize; };
        void setColors(std::vector<pColor> newColors);
        void setFunction(void(*newFunction)(int)) { function = newFunction; };
        void setState(int newState);
        
        std::pair<float, float> getPos() { return pos; };
        std::pair<float, float> getSize() { return size; };
        std::vector<pColor> getColors() { return colors; };
        void triggerFunction(int state) { function(state); };
        int getState() { return state; };
};