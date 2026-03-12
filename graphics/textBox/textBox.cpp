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
    this->drawRectangle(pos, size, outlineColor);
    this->drawRectangle({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, insideColor);
    if (selected) this->drawRectangle(barPos, barSize, barColor);
    
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
        else if (key == 8 && text.size() >= 1 && barAltPos >= 0) {
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
    if (this->mouseInRegion(pos, size)) {
        selected = !selected;
        screen.render();
        if (!selected)
            onEnter(text);
    }
    if (!this->mouseInRegion(pos, size) && selected) {
        selected = false;
        screen.render();
    }
}

void pGraphics::pTextBox::onSpeciaKeyPress(int key) {
    if (!selected) return;
    int oBarPos = barPos.first;
    if (key == GLUT_KEY_LEFT && barAltPos >= 0)
        barPos.first -= glutBitmapWidth(font, text.c_str()[barAltPos--]);
    if (key == GLUT_KEY_RIGHT && barAltPos + 1 <= maxBarAltPos)
        barPos.first += glutBitmapWidth(font, text.c_str()[++barAltPos]);
    if (oBarPos != barPos.first) screen.render();
}

void pGraphics::pTextBox::setPos(std::pair<double, double> newPos) {
    pos = newPos;
    setText(text);
}

void pGraphics::pTextBox::setSize(std::pair<double, double> newSize) {
    size = newSize;
    barSize = { 2, size.second - 8 };
    setText(text);
}

void pGraphics::pTextBox::setMaxChr(int newMaxChr) {
    maxChr = newMaxChr;
}

void pGraphics::pTextBox::setFont(void* newFont) {
    font = newFont;
}

void pGraphics::pTextBox::setOutlineColor(pColor newOutlineColor) {
    outlineColor = newOutlineColor;
}

void pGraphics::pTextBox::setInsideColor(pColor newInsideColor) {
    insideColor = newInsideColor;
}

void pGraphics::pTextBox::setBarColor(pColor newBarColor) {
    barColor = newBarColor;
}

void pGraphics::pTextBox::setTextColor(pColor newTextColor) {
    textColor = newTextColor;
}

void pGraphics::pTextBox::setFunction(void(*newOnEnter)(std::string)) {
    onEnter = newOnEnter;
}

void pGraphics::pTextBox::setText(std::string newText) {
    barPos = { 6 + pos.first, 4 + pos.second };
    barSize = { 2, size.second - 8 };
    barAltPos = -1;
    maxBarAltPos = -1;
    text = newText;
    for (unsigned int i = 0; i < newText.size(); ++i) {
        barPos.first += glutBitmapWidth(font, newText.at(i));
        ++barAltPos;
        ++maxBarAltPos;
    }
}

std::string pGraphics::pTextBox::getText() {
    return text;
}