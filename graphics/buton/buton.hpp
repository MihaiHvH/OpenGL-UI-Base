#pragma once

#ifdef _WIN32
    #undef interface
#endif

#include <utility>
#include "../../structs.hpp"
#include "../../interface/interface.hpp"

class pGraphics::pButon {
    private:
    bool active = false;
    /*BUTTON VARS*/

    std::pair<int, int> pos;
    std::pair<int, int> size;
    pColor initColor;
    pColor activeColor;
    void* font;
    pColor textColor;
    std::string text;
    void(*onClick)(bool);

    public:
    pButon(std::pair<int, int> pos, std::pair<int, int> size, pColor initColor, pColor activeColor,
                 void* font, pColor textColor, std::string text, void(*onClickFunction)(bool));
    ~pButon();
    void draw(pInterface interface);
    void checkClick(pInterface interface);
};