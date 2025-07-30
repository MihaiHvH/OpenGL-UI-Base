#include "textBox.hpp"
#include <cstring>
#include <string>

pGraphics::pTextBox::~pTextBox() {
    
}

pGraphics::pTextBox::pTextBox(std::pair<double, double> pPos, std::pair<double, double> pSize, int pMaxChr, void* pFont, pColor pOutlineColor, pColor pInsideColor, pColor pBarColor, pColor pTextColor, void(*pOnEnter)(std::string text)) {
    pos = pPos;
    size = pSize;
    maxChr = pMaxChr;
    font = pFont;
    outlineColor = pOutlineColor;
    insideColor = pInsideColor;
    barColor = pBarColor;
    onEnter = pOnEnter;
    textColor = pTextColor;

    barPos = { 6 + pPos.first, 4 + pPos.second };
    barSize = { 2, pSize.second - 8 };
}

void pGraphics::pTextBox::draw() {
    this->drawRect(pos, size, outlineColor);
    this->drawRect({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, insideColor);
    if (selected) this->drawRect(barPos, barSize, barColor);
    
    int sz = this->getTextSize(text.c_str(), font).second;
    this->drawText({ pos.first + 6, pos.second + (size.second / 2) + sz / 2 + 2}, font, text.c_str(), textColor);
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
                if (text.size() == 0)
                    text.push_back(key);
                else 
                    text.insert(text.begin() + barAltPos + 1, key);
                barPos.first += wsz;
                ++barAltPos;
                ++maxBarAltPos;
            }
        }
        else if (key == 8 && text.size() >= 1 && barAltPos - 1 >= -1) {
            barPos.first -= glutBitmapWidth(font, text.at(barAltPos));
            text.erase(text.begin() + barAltPos);
            --barAltPos;
            --maxBarAltPos;
        }
        else if (key == 127 && text.size() >= 1 && barAltPos < maxBarAltPos) {
            if (barAltPos == -1)
                text.erase(text.begin());
            else 
                text.erase(text.begin() + barAltPos + 1);
            --maxBarAltPos;
        }
        screen.render();
    }
}

void pGraphics::pTextBox::checkClick() {
    if (this->mouseInRegion(pos, size) && screen.leftClick) {
        selected = !selected;
        if (!selected)
            onEnter(text);
    }
    if (!this->mouseInRegion(pos, size) && screen.leftClick && selected)
        selected = false, onEnter(text);
}

void pGraphics::pTextBox::onSpeciaKeyPress(int key) {
    if (key == GLUT_KEY_LEFT && barAltPos - 1 >= -1)
        barPos.first -= glutBitmapWidth(font, text.c_str()[barAltPos--]);
    if (key == GLUT_KEY_RIGHT && barAltPos + 1 <= maxBarAltPos)
        barPos.first += glutBitmapWidth(font, text.c_str()[++barAltPos]);
    screen.render();
}

void pGraphics::pTextBox::updatePos(std::pair<double, double> pPos) {
    pos = pPos;
}

void pGraphics::pTextBox::updateSize(std::pair<double, double> pSize) {
    size = pSize;
}