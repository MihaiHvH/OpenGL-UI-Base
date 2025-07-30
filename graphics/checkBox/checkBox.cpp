#include "checkBox.hpp"

pGraphics::pCheckBox::~pCheckBox() {

}

pGraphics::pCheckBox::pCheckBox(std::pair<double, double> pPos, std::pair<double, double> pSize, void* pFont, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, pColor pOnColor, pColor pOffColor, void(*pOnStateChange)(bool)) {
    pos = pPos;
    size = pSize;
    font = pFont;
    text = pText;
    textOrientation = pTextOrientation;
    textColor = pTextColor;
    outlineColor = pOutlineColor;
    onColor = pOnColor;
    offColor = pOffColor;
    onChangeState = pOnStateChange;
}

void pGraphics::pCheckBox::checkClick() {
    if (this->mouseInRegion(pos, size) && screen.leftClick)
        active = !active, onChangeState(active);
}

void pGraphics::pCheckBox::draw() {
    this->drawRect(pos, size, outlineColor);
    
    pColor color;
    active ? color = onColor : color = offColor;
    this->drawRect({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, color);

    int wSz = this->getTextSize(text.c_str(), font).second;

    if (textOrientation) { //right
        this->drawText({ pos.first + 10 + size.first, (pos.second + (size.second / 2)) + wSz / 2 }, font, text.c_str(), textColor);
    }
    else { //left
        const unsigned char* str = reinterpret_cast<const unsigned char*>(text.c_str());
        int sz = glutBitmapLength(font, str);
        this->drawText({ pos.first - sz - 10, 0 }, font, text.c_str(), textColor);
    }
}

void pGraphics::pCheckBox::updatePos(std::pair<double, double> pPos) {
    pos = pPos;
}

void pGraphics::pCheckBox::updateSize(std::pair<double, double> pSize) {
    size = pSize;
}