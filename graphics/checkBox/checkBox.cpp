#include "checkBox.hpp"

pGraphics::pCheckBox::~pCheckBox() {

}

pGraphics::pCheckBox::pCheckBox(std::pair<int, int> pPos, std::pair<int, int> pSize, void* pFont, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, pColor pOnColor, pColor pOffColor, void(*pOnStateChange)(bool)) {
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

void pGraphics::pCheckBox::checkClick(pInterface interface) {
    if (interface.graphics.mouseInRegion(interface.screen.mousePointer, pos, size) && interface.screen.leftClick)
        active = !active, onChangeState(active);
}

void pGraphics::pCheckBox::draw(pInterface interface) {
    interface.graphics.drawRect(pos, size, outlineColor);
    
    pColor color;
    active ? color = onColor : color = offColor;
    interface.graphics.drawRect({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, color);

    int wSz = 0; //max WText
    for (size_t i = 0; i < strlen(text.c_str()); ++i)
        if (wSz < glutBitmapWidth(font, text.c_str()[i]))
            wSz = glutBitmapWidth(font, text.c_str()[i]);
            
    if (textOrientation) { //right
        interface.graphics.drawText({ pos.first + 10 + size.first, (pos.second + (size.second / 2)) + wSz / 2 }, font, text.c_str(), textColor);
    }
    else { //left
        const unsigned char* str = reinterpret_cast<const unsigned char*>(text.c_str());
        int sz = glutBitmapLength(font, str);
        interface.graphics.drawText({ pos.first - sz - 10, 0 }, font, text.c_str(), textColor);
    }
}