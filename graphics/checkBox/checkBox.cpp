#include "checkBox.hpp"

pGraphics::pCheckBox::~pCheckBox() {

}

pGraphics::pCheckBox::pCheckBox(std::pair<double, double> pPos, std::pair<double, double> pSize, std::string pFontLocation, int pFontSize, std::string pText, bool pTextOrientation, pColor pTextColor, pColor pOutlineColor, std::vector<pColor> pColors, void(*pFunction)(int)) {
    pos = pPos;
    size = pSize;
    textOrientation = pTextOrientation;
    outlineColor = pOutlineColor;
    colors = pColors;
    function = pFunction;

    textObj = new pGraphics::pText({ 0, 0 }, pFontLocation, pFontSize, pText, pTextColor);
}

void pGraphics::pCheckBox::checkClick() {
    if (this->mouseInRegion(pos, size)) {
        if (++state >= colors.size()) state = 0;
        screen.render();
        function(state);
    }
}

void pGraphics::pCheckBox::init() {
    textObj->load();
}

void pGraphics::pCheckBox::draw() {
    if (colors.empty()) return;

    this->drawRectangle(pos, size, outlineColor);
    this->drawRectangle({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, colors.at(state));

    std::pair<double, double> textSize = textObj->getTextSize();
    if (textOrientation) //right
        textObj->setPos({ pos.first + 10 + size.first, (pos.second + (size.second / 2)) + textSize.second / 2 });
    else //left
        textObj->setPos({ pos.first - textSize.first - 10, pos.second + (size.second / 2) + textSize.second / 2 });
    textObj->draw();
}

void pGraphics::pCheckBox::setColors(std::vector<pColor> newColors) {
    if (newColors.empty()) return;
    colors = newColors;
    if (state >= colors.size()) state = 0;
}

void pGraphics::pCheckBox::setState(int newState) {
    if (newState >= 0 && newState < colors.size())
        state = newState;
}