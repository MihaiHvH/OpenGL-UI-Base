#pragma once

#include "../../main.hpp"

class pGraphics::pTextBox : public pGraphics::pElement {
    private: 
        bool selected = false;
        std::pair<float, float> barPos;
        std::pair<float, float> barSize;
        int maxChr;
        pColor insideColor;
        pColor barColor;
        void(*function)(std::string text);
        std::string text = "";
        int barAltPos = -1;
        int maxBarAltPos = -1;

        pGraphics::pText* textObj;

    public:
        //if pMaxChr == -1 => auto
        pTextBox(pGraphics* gfx, std::pair<float, float> pos, std::pair<float, float> size, int maxChr, std::string fontLocation, int fontSize, pColor insideColor, pColor barColor, pColor textColor, void(*function)(std::string));
        ~pTextBox();

        void init();
        void draw();
        void checkClick();
        void onKeyPress(unsigned int key);
        void onSpeciaKeyPress(int key, int action);

        void setPos(std::pair<float, float> newPos);
        void setSize(std::pair<float, float> newSize);
        void setMaxChr(int newMaxChr) { maxChr = newMaxChr; };
        void setInsideColor(pColor newInsideColor) { insideColor = newInsideColor; };
        void setBarColor(pColor newBarColor) { barColor = newBarColor; };
        void setFunction(void(*newFunction)(std::string)) { function = newFunction; };
        void setText(std::string newText);

        pGraphics::pText* getTextObj() { return textObj; };
        std::string getText() { return text; };
};