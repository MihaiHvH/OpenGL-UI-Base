#include "button.hpp"

pGraphics::pButton::~pButton() {
    
}

pGraphics::pButton::pButton(pGraphics* pGfx, std::pair<double, double> pPos, std::pair<double, double> pSize, std::vector<pColor> pColors, void(*pFunction)(int)) {
    this->gfx = pGfx;
    pos = pPos;
    size = pSize;
    colors = pColors;
    function = pFunction;
}

void pGraphics::pButton::checkClick() {
    if (gfx->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        function(state);
        screen.render();
    }
}

void pGraphics::pButton::draw() {
    if (colors.empty()) return;
    if (this->borderSize != 0)
        gfx->drawRectangle({ pos.first - this->borderSize, pos.second - this->borderSize }, { size.first + 2 * this->borderSize, size.second + 2 * this->borderSize }, this->borderColor);
    gfx->drawRectangle(pos, size, colors.at(state));
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