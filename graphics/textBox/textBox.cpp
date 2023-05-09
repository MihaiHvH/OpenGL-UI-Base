#include "textBox.hpp"
#include <cstring>
#include <string>

pGraphics::pTextBox::~pTextBox() {
    
}

pGraphics::pTextBox::pTextBox(std::pair<int, int> pPos, std::pair<int, int> pSize, int pMaxChr, void* pFont, pColor pOutlineColor, pColor pInsideColor, pColor pBarColor, pColor pTextColor, void(*pRender)(void), void(*pOnEnter)(std::string text)) {
    pos = pPos;
    size = pSize;
    maxChr = pMaxChr;
    font = pFont;
    outlineColor = pOutlineColor;
    insideColor = pInsideColor;
    barColor = pBarColor;
    render = pRender;
    onEnter = pOnEnter;
    textColor = pTextColor;

    barPos = { 6 + pPos.first, 4 + pPos.second };
    barSize = { 2, pSize.second - 8 };
}

void pGraphics::pTextBox::draw(pInterface interface) {
    interface.graphics.drawRect(pos, size, outlineColor);
    interface.graphics.drawRect({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, insideColor);
    if (selected) interface.graphics.drawRect(barPos, barSize, barColor);

    int sz = 0; 
    if (text.size() >= 0) sz = glutBitmapWidth(font, text[0]);

    interface.graphics.drawText({ pos.first + 6, pos.second + (size.second / 2) + sz / 2 }, font, text.c_str(), textColor);
}

void pGraphics::pTextBox::onKeyPress(unsigned char key) {
    if (selected) {
        const unsigned char* str = reinterpret_cast<const unsigned char*>(text.c_str());
        int sz = glutBitmapLength(font, str);

        if (key == 13) //enter
            selected = false, onEnter(text);
        else if (key != 8 && key != 127 && (maxBarAltPos + 2 <= maxChr && maxChr != -1)) {
            text.insert(text.begin() + barAltPos + 1, key);
            barPos.first += glutBitmapWidth(font, key);
            ++barAltPos;
            ++maxBarAltPos;
        }
        else if (key != 8 && key != 127 && maxChr == -1) {
            int wsz = glutBitmapWidth(font, key);
            if (sz + wsz + 8 <= size.first) {
                text.insert(text.begin() + barAltPos + 1, key);
                barPos.first += wsz;
                ++barAltPos;
                ++maxBarAltPos;
            }
        }
        else if (key == 8 && text.size() >= 1 && barAltPos - 1 >= -1) {
            barPos.first -= glutBitmapWidth(font, text.at(barAltPos));
            text.erase(text.begin() + barAltPos);
            barAltPos--;
            --maxBarAltPos;
        }
        else if (key == 127 && text.size() >= 1 && barAltPos < maxBarAltPos) {
            text.erase(text.begin() + barAltPos + 1);
            --maxBarAltPos;
        }
        render();
    }
}

void pGraphics::pTextBox::checkClick(pInterface interface) {
    if (interface.graphics.mouseInRegion(interface.screen.mousePointer, pos, size) && interface.screen.leftClick) {
        selected = !selected;
        if (!selected)
            onEnter(text);
    }
    if (!interface.graphics.mouseInRegion(interface.screen.mousePointer, pos, size) && interface.screen.leftClick && selected)
        selected = false, onEnter(text);
}

void pGraphics::pTextBox::onSpeciaKeyPress(int key) {
    if (key == GLUT_KEY_LEFT && barAltPos - 1 >= -1)
        barPos.first -= glutBitmapWidth(font, text.c_str()[barAltPos--]);
    if (key == GLUT_KEY_RIGHT && barAltPos + 1 <= maxBarAltPos)
        barPos.first += glutBitmapWidth(font, text.c_str()[++barAltPos]);
    render();
}