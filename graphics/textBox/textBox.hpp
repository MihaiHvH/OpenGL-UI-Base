#pragma once

#include "../../main.hpp"

class pGraphics::pTextBox {
    private: 
    bool selected = false;
    int incr = 0;
    std::pair<int, int> barPos;
    std::pair<int, int> barSize;
    std::pair<int, int> pos;
    std::pair<int, int> size;
    int maxChr;
    void* font;
    pColor outlineColor;
    pColor insideColor;
    pColor barColor;
    pColor textColor;
    void(*onEnter)(std::string text);
    void(*render)(void);
    std::string text = "";
    std::string oText = "";
    int barAltPos = -1;
    int maxBarAltPos = -1;

    public:
    //if pMaxChr == -1 => auto
    pTextBox(std::pair<int, int> pPos, std::pair<int, int> pSize, int pMaxChr, void* pFont, pColor pOutlineColor, pColor pInsideColor, pColor pBarColor, pColor pTextColor, void(*pRender)(void), void(*pOnEnter)(std::string text));
    ~pTextBox();

    void onKeyPress(unsigned char key);
    void checkClick(pInterface interface);
    void draw(pInterface interface);
    void onSpeciaKeyPress(int key);
};