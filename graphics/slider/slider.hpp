#pragma once

#include "../../main.hpp"

class pGraphics::pSlider : public pGraphics::pElement {
    private:
        std::pair<float, float> minMax;
        int decimals;
        int valueTextSize;
        pColor onColor;
        pColor offColor;
        void(*function)(float value);

        float value;
        float pxOn;
        float pxOff;
        std::string valueText;

        pGraphics::pText* valueTextObj;

    public:
        pSlider(pGraphics* gfx, std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, pColor onColor, pColor offColor, pColor valueTextColor, void(*function)(float));
        ~pSlider();

        void init();
        void draw();
        void handleMouse();

        void setPos(std::pair<float, float> newPos);
        void setSize(std::pair<float, float> newSize);
        void setMinMax(std::pair<float, float> newMinMax);
        void setDecimals(int newDecimals);
        void setOnColor(pColor newOnColor) { onColor = newOnColor; };
        void setOffColor(pColor newOffColor) { offColor = newOffColor; };
        void setFunction(void(*newFunction)(float)) { function = newFunction; };
        void setValue(float newValue);
        
        std::pair<float, float> getPos() { return this->pos; };
        std::pair<float, float> getSize() { return this->size; };
        pGraphics::pText* getValueTextObj() { return valueTextObj; };
        float getValue() { return value; };
};