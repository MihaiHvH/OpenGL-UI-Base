#pragma once

#include "../../main.hpp"

class pGraphics::pTextBox : public pGraphics {
    private: 
    bool selected = false;
    int incr = 0;
    std::pair<double, double> barPos;
    std::pair<double, double> barSize;
    std::pair<double, double> pos;
    std::pair<double, double> size;
    int maxChr;
    void* font;
    pColor outlineColor;
    pColor insideColor;
    pColor barColor;
    pColor textColor;
    void(*onEnter)(std::string text);
    std::string text = "";
    std::string oText = "";
    int barAltPos = -1;
    int maxBarAltPos = -1;

    public:
    //if pMaxChr == -1 => auto
    pTextBox(std::pair<double, double> pPos, std::pair<double, double> pSize, int pMaxChr, void* pFont, pColor pOutlineColor, pColor pInsideColor, pColor pBarColor, pColor pTextColor, void(*pOnEnter)(std::string text));
    ~pTextBox();

    void onKeyPress(unsigned char key);
    void checkClick();
    void draw();
    void updatePos(std::pair<double, double> pPos);
    void updateSize(std::pair<double, double> pSize);
    void onSpeciaKeyPress(int key);
};