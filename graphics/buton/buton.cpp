#include "buton.hpp"

pGraphics::pButon::~pButon() {

}

pGraphics::pButon::pButon(std::pair<double, double> pPos, std::pair<double, double> pSize, std::vector<pColor> pColors, void* pFont, pColor pTextColor, std::string pText, void(*pOnChangeState)(int)) {
    pos = pPos;
    size = pSize;
    colors = pColors;
    font = pFont;
    textColor = pTextColor;
    text = pText;
    onChangeState = pOnChangeState;
}

void pGraphics::pButon::checkClick() {
    if (this->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        onChangeState(state);
        screen.render();
    }
}

void pGraphics::pButon::draw() {
    if (colors.empty()) return;
    std::pair<int, int> textSize = this->getTextSize(text.c_str(), font);
    this->drawRectangle(pos, size, colors.at(state));
    this->drawText({ pos.first + ((size.first - textSize.first) / 2), pos.second + (size.second / 2) + textSize.second / 2 }, font, text.c_str(), textColor);   
}

void pGraphics::pButon::setPos(std::pair<double, double> newPos) {
    pos = newPos;
}

void pGraphics::pButon::setSize(std::pair<double, double> newSize) {
    size = newSize;
}

void pGraphics::pButon::setColors(std::vector<pColor> newColors) {
    if (newColors.empty()) return;
    colors = newColors;
    if (state >= colors.size()) state = 0;
}

void pGraphics::pButon::setFont(void* newFont) {
    font = newFont;
}

void pGraphics::pButon::setText(std::string newText) {
    text = newText;
}

void pGraphics::pButon::setTextColor(pColor newTextColor) {
    textColor = newTextColor;
}

void pGraphics::pButon::setFunction(void(*newOnChangeState)(int)) {
    onChangeState = newOnChangeState;
}

void pGraphics::pButon::setState(int newState) {
    if (newState >= 0 && newState < colors.size())
        state = newState;
}

int pGraphics::pButon::getState() {
    return state;
}