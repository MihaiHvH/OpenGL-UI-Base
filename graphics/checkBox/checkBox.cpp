#include "checkBox.hpp"

pGraphics::pCheckBox::~pCheckBox() {

}

pGraphics::pCheckBox::pCheckBox(std::pair<double, double> pPos, std::pair<double, double> pSize, void* pFont, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, std::vector<pColor> pColors, void(*pOnStateChange)(int)) {
    pos = pPos;
    size = pSize;
    font = pFont;
    text = pText;
    textOrientation = pTextOrientation;
    textColor = pTextColor;
    outlineColor = pOutlineColor;
    colors = pColors;
    onChangeState = pOnStateChange;
}

void pGraphics::pCheckBox::checkClick() {
    if (this->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        screen.render();
        onChangeState(state);
    }
}

void pGraphics::pCheckBox::draw() {
    if (colors.empty()) return;
    int wSz = this->getTextSize(text.c_str(), font).second;

    this->drawRectangle(pos, size, outlineColor);
    this->drawRectangle({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, colors.at(state));

    if (textOrientation) //right
        this->drawText({ pos.first + 10 + size.first, (pos.second + (size.second / 2)) + wSz / 2 }, font, text.c_str(), textColor);
    else { //left
        const unsigned char* str = reinterpret_cast<const unsigned char*>(text.c_str());
        int sz = glutBitmapLength(font, str);
        this->drawText({ pos.first - sz - 10, pos.second + (size.second / 2) + wSz / 2 }, font, text.c_str(), textColor);
    }
}

void pGraphics::pCheckBox::setPos(std::pair<double, double> newPos) {
    pos = newPos;
}

void pGraphics::pCheckBox::setSize(std::pair<double, double> newSize) {
    size = newSize;
}

void pGraphics::pCheckBox::setFont(void* newFont) {
    font = newFont;
}

void pGraphics::pCheckBox::setText(std::string newText) {
    text = newText;
}

void pGraphics::pCheckBox::setTextOrientation(bool newTextOrientation) {
    textOrientation = newTextOrientation;
}

void pGraphics::pCheckBox::setTextColor(pColor newTextColor) {
    textColor = newTextColor;
}

void pGraphics::pCheckBox::setOutlineColor(pColor newOutlineColor) {
    outlineColor = newOutlineColor;
}

void pGraphics::pCheckBox::setColors(std::vector<pColor> newColors) {
    if (newColors.empty()) return;
    colors = newColors;
    if (state >= colors.size()) state = 0;
}

void pGraphics::pCheckBox::setFunction(void(*newOnChangeState)(int)) {
    onChangeState = newOnChangeState;
}

void pGraphics::pCheckBox::setState(int newState) {
    if (newState >= 0 && newState < colors.size())
        state = newState;
}

int pGraphics::pCheckBox::getState() {
    return state;
}