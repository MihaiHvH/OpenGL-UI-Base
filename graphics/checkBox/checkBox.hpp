#pragma once

#include "../../main.hpp"

class pGraphics::pCheckBox {
    private:
    bool active = false;
    
    std::pair<int, int> pos;
    std::pair<int, int> size;
    void* font;
    std::string text;
    bool textOrientation;
    pColor textColor;
    pColor outlineColor;
    pColor onColor;
    pColor offColor;
    void(*onChangeState)(bool);

    public:
    pCheckBox(std::pair<int, int> pPos, std::pair<int, int> pSize, void* pFont, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, pColor pOnColor, pColor pOffColor, void(*pOnStateChange)(bool));
    ~pCheckBox();

    void checkClick(pInterface interface);
    void draw(pInterface interface);
};