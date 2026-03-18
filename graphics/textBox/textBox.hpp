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
    std::string fontLocation;
    int fontSize;
    pColor outlineColor;
    pColor insideColor;
    pColor barColor;
    pColor textColor;
    void(*onEnter)(std::string text);
    std::string text = "";
    std::string oText = "";
    int barAltPos = -1;
    int maxBarAltPos = -1;

    pGraphics::pText* textObj;

    double barX;

    public:
    //if pMaxChr == -1 => auto
    pTextBox(std::pair<double, double> pPos, std::pair<double, double> pSize, int pMaxChr, std::string pFontLocation, int pFontSize, pColor pOutlineColor, pColor pInsideColor, pColor pBarColor, pColor pTextColor, void(*pOnEnter)(std::string));
    ~pTextBox();

    void init();

    void onKeyPress(unsigned int key);
    void checkClick();
    void draw();
    void onSpeciaKeyPress(int key, int action);

    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setMaxChr(int newMaxChr);
    void setFont(void* newFont);
    void setOutlineColor(pColor newOutlineColor);
    void setInsideColor(pColor newInsideColor);
    void setBarColor(pColor newBarColor);
    void setTextColor(pColor newTextColor);
    void setFunction(void(*newOnEnter)(std::string));
    void setText(std::string newText);
    std::string getText();
};