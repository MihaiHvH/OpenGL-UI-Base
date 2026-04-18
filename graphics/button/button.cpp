#include "button.hpp"

pGraphics::pButton::~pButton() {
    
}

pGraphics::pButton::pButton(pGraphics* pGfx, std::pair<float, float> pPos, std::pair<float, float> pSize, std::vector<pColor> pColors, void(*pFunction)(int)) {
    gfx = pGfx;
    pos = pPos;
    size = pSize;
    colors = pColors;
    function = pFunction;
}

void pGraphics::pButton::checkClick() {
    if (gfx->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        function(state);
    }
}

void pGraphics::pButton::draw() {
    if (colors.empty() || !showing) return;
    if (borderSize != 0)
        gfx->drawRectangle({ pos.first - borderSize, pos.second - borderSize }, { size.first + 2 * borderSize, size.second + 2 * borderSize }, borderColor);
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