#include "button.hpp"

pGraphics::pButton::~pButton() {

}

pGraphics::pButton::pButton(std::pair<double, double> pPos, std::pair<double, double> pSize, std::vector<pColor> pColors, std::string pFontLocation, int pFontSize, pColor pTextColor, std::string pText, void(*pFunction)(int)) {
    pos = pPos;
    size = pSize;
    colors = pColors;
    function = pFunction;

    textObj = new pGraphics::pText({ 10, 10 }, pFontLocation, pFontSize, pText, pTextColor);
}

void pGraphics::pButton::checkClick() {
    if (this->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        function(state);
        screen.render();
    }
}

void pGraphics::pButton::draw() {
    if (colors.empty()) return;
    this->drawRectangle(pos, size, colors.at(state));
    std::pair<double, double> textSize = textObj->getTextSize();
    textObj->setPos({ pos.first + ((size.first - textSize.first) / 2), pos.second + (size.second + textSize.second) / 2 });
    textObj->draw();
}

void pGraphics::pButton::init() {
    textObj->load();
}

void pGraphics::pButton::setColors(std::vector<pColor> newColors) {
    if (newColors.empty()) return;
    colors = newColors;
    if (state >= colors.size()) state = 0;
}

void pGraphics::pButton::setState(int newState) {
    if (newState >= 0 && newState < colors.size())
        state = newState;
}