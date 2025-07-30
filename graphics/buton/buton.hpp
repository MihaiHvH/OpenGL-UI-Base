#pragma once

#include <utility>
#include "../../structs.hpp"
#include "../../interface/interface.hpp"

class pGraphics::pButon : public pGraphics {
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
    void draw();
    void checkClick();
    void updatePos(std::pair<double, double> pPos);
    void updateSize(std::pair<double, double> pSize);
};