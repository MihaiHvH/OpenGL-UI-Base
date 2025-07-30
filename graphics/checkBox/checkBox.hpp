#pragma once

#include "../../main.hpp"

class pGraphics::pCheckBox : public pGraphics {
    private:
    bool active = false;
    
    std::pair<double, double> pos;
    std::pair<double, double> size;
    void* font;
    std::string text;
    bool textOrientation;
    pColor textColor;
    pColor outlineColor;
    pColor onColor;
    pColor offColor;
    void(*onChangeState)(bool);

    public:
    pCheckBox(std::pair<double, double> pPos, std::pair<double, double> pSize, void* pFont, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, pColor pOnColor, pColor pOffColor, void(*pOnStateChange)(bool));
    ~pCheckBox();

    void checkClick();
    void draw();
    void updatePos(std::pair<double, double> pPos);
    void updateSize(std::pair<double, double> pSize);
};