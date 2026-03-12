#pragma once

#include "../../main.hpp"

class pGraphics::pCheckBox : public pGraphics {
    private:
    int state = 0;
    
    std::pair<double, double> pos;
    std::pair<double, double> size;
    void* font;
    std::string text;
    bool textOrientation;
    pColor textColor;
    pColor outlineColor;
    std::vector<pColor> colors;
    void(*onChangeState)(int);

    public:
    pCheckBox(std::pair<double, double> pPos, std::pair<double, double> pSize, void* pFont, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, std::vector<pColor> colors, void(*pOnStateChange)(int));
    ~pCheckBox();

    void checkClick();
    void draw();

    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setFont(void* newFont);
    void setText(std::string newText);
    void setTextOrientation(bool newTextOrientation);
    void setTextColor(pColor newTextColor);
    void setOutlineColor(pColor newOutlineColor);
    void setColors(std::vector<pColor> newColors);
    void setFunction(void(*newOnChangeState)(int));
    void setState(int newState);
    int getState();
};