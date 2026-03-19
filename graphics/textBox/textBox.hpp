#pragma once

#include "../../main.hpp"

class pGraphics::pTextBox : public pGraphics {
    private: 
    bool selected = false;
    std::pair<double, double> barPos;
    std::pair<double, double> barSize;
    std::pair<double, double> pos;
    std::pair<double, double> size;
    int maxChr;
    pColor outlineColor;
    pColor insideColor;
    pColor barColor;
    void(*function)(std::string text);
    std::string text = "";
    int barAltPos = -1;
    int maxBarAltPos = -1;

    pGraphics::pText* textObj;

    public:
    //if pMaxChr == -1 => auto
    pTextBox(std::pair<double, double> pos, std::pair<double, double> size, int maxChr, std::string fontLocation, int fontSize, pColor outlineColor, pColor insideColor, pColor barColor, pColor textColor, void(*function)(std::string));
    ~pTextBox();

    void init();
    void draw();
    void checkClick();
    void onKeyPress(unsigned int key);
    void onSpeciaKeyPress(int key, int action);

    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setMaxChr(int newMaxChr) { maxChr = newMaxChr; };
    void setOutlineColor(pColor newOutlineColor) { outlineColor = newOutlineColor; };
    void setInsideColor(pColor newInsideColor) { insideColor = newInsideColor; };
    void setBarColor(pColor newBarColor) { barColor = newBarColor; };
    void setFunction(void(*newFunction)(std::string)) { function = newFunction; };
    void setText(std::string newText);

    pGraphics::pText* getTextObj() { return textObj; };
    std::string getText() { return text; };
};