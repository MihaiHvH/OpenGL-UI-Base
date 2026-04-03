#include "button.hpp"

pGraphics::pButton::~pButton() {
    
}

pGraphics::pButton::pButton(std::pair<double, double> pPos, std::pair<double, double> pSize, std::vector<pColor> pColors, void(*pFunction)(int)) {
    pos = pPos;
    size = pSize;
    colors = pColors;
    function = pFunction;
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