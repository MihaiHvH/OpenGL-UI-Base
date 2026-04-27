#pragma once

#include "../../main.hpp"

class pGraphics::pSlider : public pGraphics::pElement {
    private:
        std::pair<float, float> minMax;
        int decimals;
        int valueTextSize;
        colors::pColor onColor;
        colors::pColor offColor;
        void(*function)(float value);

        float value;
        float pxOn;
        float pxOff;
        std::string valueText;

        pGraphics::pText* valueTextObj;

    public:
        pSlider(pGraphics* gfx, std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, colors::pColor onColor, colors::pColor offColor, colors::pColor valueTextColor, void(*function)(float));
        ~pSlider();

        void init();
        void draw();
        void handleMouse();

        void setPos(std::pair<float, float> newPos);
        void setSize(std::pair<float, float> newSize);
        void setMinMax(std::pair<float, float> newMinMax);
        void setDecimals(int newDecimals);
        void setOnColor(colors::pColor newOnColor) { onColor = newOnColor; };
        void setOffColor(colors::pColor newOffColor) { offColor = newOffColor; };
        void setFunction(void(*newFunction)(float)) { function = newFunction; };
        void setValue(float newValue);
        
        std::pair<float, float> getPos() { return pos; };
        std::pair<float, float> getSize() { return size; };
        std::pair<float, float> getMinMax();
        int getDecimals() { return decimals; };
        colors::pColor getOnColor() { return onColor; };
        colors::pColor getOffColor() { return offColor; };
        void triggerFunction(float value) { function(value); };
        pGraphics::pText* getValueTextObj() { return valueTextObj; };
        float getValue() { return value; };
};