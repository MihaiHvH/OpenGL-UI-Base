#pragma once

#include <utility>
#include "../../structs.hpp"
#include "../../interface/interface.hpp"

class pGraphics::pButon {
    private:
    bool active = false;
    /*BUTTON VARS*/

    std::pair<double, double> pos;
    std::pair<double, double> size;
    pColor initColor;
    pColor activeColor;
    void* font;
    pColor textColor;
    std::string text;
    void(*onClick)(bool);

    public:
    pButon(std::pair<double, double> pos, std::pair<double, double> size, pColor initColor, pColor activeColor,
                 void* font, pColor textColor, std::string text, void(*onClickFunction)(bool));
    ~pButon();
    void draw(pInterface interface);
    void checkClick(pInterface interface);
    void updatePos(std::pair<double, double> pPos);
    void updateSize(std::pair<double, double> pSize);
};