#pragma once

#include "../../main.hpp"

class pGraphics::pButton : public pGraphics {
    private:
    int state = 0;
    /*BUTTON VARS*/

    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::vector<pColor> colors;
    std::string fontLocation;
    int fontSize;
    pColor textColor;
    std::string text;
    void(*onChangeState)(int);
    pGraphics::pText *textObj;
    bool isTextLoaded = false;

    public:
    pButton(std::pair<double, double> pos, std::pair<double, double> size, std::vector<pColor> colors, std::string pFontLocation, int pFontSize, pColor textColor, std::string text, void(*onChangeState)(int));
    ~pButton();
    void init();
    void draw();
    void checkClick();
    
    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setColors(std::vector<pColor> newColors);
    void setFont(void* newFont);
    void setText(std::string newText);
    void setTextColor(pColor newTextColor);
    void setFunction(void(*newOnChangeState)(int));
    void setState(int newState);
    int getState();
};