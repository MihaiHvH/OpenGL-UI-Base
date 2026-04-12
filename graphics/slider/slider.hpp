#pragma once

#include "../../main.hpp"

class pGraphics::pSlider : public pGraphics::pElement {
    private:
        std::pair<double, double> minMax;
        int decimals;
        int valueTextSize;
        pColor onColor;
        pColor offColor;
        void(*function)(double value);

        double value;
        double pxOn;
        double pxOff;
        std::string valueText;

        pGraphics::pText* valueTextObj;

    public:
        pSlider(pGraphics* gfx, std::pair<double, double> pos, std::pair<double, double> size, std::pair<double, double> minMax, int decimals, std::string fontLocation, int valueTextSize, pColor onColor, pColor offColor, pColor valueTextColor, void(*function)(double));
        ~pSlider();

        void init();
        void draw();
        void handleMouse();

        void setPos(std::pair<double, double> newPos);
        void setSize(std::pair<double, double> newSize);
        void setMinMax(std::pair<double, double> newMinMax);
        void setDecimals(int newDecimals);
        void setOnColor(pColor newOnColor) { onColor = newOnColor; };
        void setOffColor(pColor newOffColor) { offColor = newOffColor; };
        void setFunction(void(*newFunction)(double)) { function = newFunction; };
        void setValue(double newValue);
        
        std::pair<double, double> getPos() { return this->pos; };
        std::pair<double, double> getSize() { return this->size; };
        pGraphics::pText* getValueTextObj() { return valueTextObj; };
        double getValue() { return value; };
};