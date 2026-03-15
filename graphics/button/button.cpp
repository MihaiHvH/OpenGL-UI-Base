#include "button.hpp"

pGraphics::pButton::~pButton() {

}

pGraphics::pButton::pButton(std::pair<double, double> pPos, std::pair<double, double> pSize, std::vector<pColor> pColors, void* pFont, pColor pTextColor, std::string pText, void(*pOnChangeState)(int)) {
    pos = pPos;
    size = pSize;
    colors = pColors;
    font = pFont;
    textColor = pTextColor;
    text = pText;
    onChangeState = pOnChangeState;
}

void pGraphics::pButton::checkClick() {
    if (this->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        onChangeState(state);
        screen.render();
    }
}

void pGraphics::pButton::draw() {
    if (colors.empty()) return;
    std::pair<int, int> textSize = this->getTextSize(text, font);
    this->drawRectangle(pos, size, colors.at(state));
    this->drawText({ pos.first + ((size.first - textSize.first) / 2), pos.second + (size.second / 2) + textSize.second / 2 }, font, text, textColor);   
}

void pGraphics::pButton::setPos(std::pair<double, double> newPos) {
    pos = newPos;
}

void pGraphics::pButton::setSize(std::pair<double, double> newSize) {
    size = newSize;
}

void pGraphics::pButton::setColors(std::vector<pColor> newColors) {
    if (newColors.empty()) return;
    colors = newColors;
    if (state >= colors.size()) state = 0;
}

void pGraphics::pButton::setFont(void* newFont) {
    font = newFont;
}

void pGraphics::pButton::setText(std::string newText) {
    text = newText;
}

void pGraphics::pButton::setTextColor(pColor newTextColor) {
    textColor = newTextColor;
}

void pGraphics::pButton::setFunction(void(*newOnChangeState)(int)) {
    onChangeState = newOnChangeState;
}

void pGraphics::pButton::setState(int newState) {
    if (newState >= 0 && newState < colors.size())
        state = newState;
}

int pGraphics::pButton::getState() {
    return state;
}