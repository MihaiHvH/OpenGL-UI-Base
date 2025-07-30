#include "../../main.hpp"
#include "buton.hpp"

#ifdef _WIN32
    #undef interface
#endif

pGraphics::pButon::~pButon() {

}

pGraphics::pButon::pButon(std::pair<double, double> pPos, std::pair<double, double> pSize, pColor pInitColor, pColor pActiveColor,
                 void* pFont, pColor pTextColor, std::string pText, void(*onClickFunction)(bool)) {
    pos = pPos;
    size = pSize;
    initColor = pInitColor;
    activeColor = pActiveColor;
    font = pFont;
    textColor = pTextColor;
    text = pText;
    onClick = onClickFunction;
}

void pGraphics::pButon::checkClick() {
    if (this->mouseInRegion(pos, size) && screen.leftClick)
        active = !active, onClick(active);
}

void pGraphics::pButon::draw() {
    pColor color;
    active ? color = activeColor : color = initColor;
    std::pair<int, int> textSize = this->getTextSize(text.c_str(), font);
    this->drawRect(pos, size, color);
    this->drawText({ pos.first + ((size.first - textSize.first) / 2), pos.second + (size.second / 2) + textSize.second / 2 }, font, text.c_str(), textColor);   
}

void pGraphics::pButon::updatePos(std::pair<double, double> pPos) {
    pos = pPos;
}

void pGraphics::pButon::updateSize(std::pair<double, double> pSize) {
    size = pSize;
}