#include "textBox.hpp"
#include <cstring>
#include <string>

pGraphics::pTextBox::~pTextBox() {
    delete textObj;
}

pGraphics::pTextBox::pTextBox(pGraphics* pGfx, std::pair<float, float> pPos, std::pair<float, float> pSize, int pMaxChr, std::string pFontLocation, int pFontSize, colors::pColor pInsideColor, colors::pColor pBarColor, colors::pColor pTextColor, void(*pFunction)(std::string text)) {
    gfx = pGfx;
    pos = pPos;
    size = pSize;
    maxChr = pMaxChr;
    insideColor = pInsideColor;
    barColor = pBarColor;
    function = pFunction;

    barPos = { 4 + pPos.first, 4 + pPos.second };
    barSize = { 2, pSize.second - 8 };

    textObj = new pGraphics::pText(gfx, { 0, 0 }, pFontLocation, pFontSize, text, pTextColor);
}

void pGraphics::pTextBox::draw() {
    if (!showing)
        return;
        
    if (borderSize != 0)
        gfx->drawRectangle({ pos.first - borderSize, pos.second - borderSize }, { size.first + 2 * borderSize, size.second + 2 * borderSize }, borderColor);
    
    gfx->drawRectangle(pos, size, insideColor);
    
    float textHeight = textObj->getTextSize().second;
    textObj->setPos({ pos.first + 4, pos.second + (size.second / 2) + textHeight / 2 });
    textObj->setText(text);
    textObj->draw();

    if (selected) gfx->drawRectangle(barPos, barSize, barColor);
}

void pGraphics::pTextBox::init() {
    textObj->load();
}

void pGraphics::pTextBox::onKeyPress(unsigned int key) {
    if (!selected) return;
    if (maxBarAltPos + 2 <= maxChr && maxChr != -1) {
        text.insert(text.begin() + barAltPos + 1, (char)key);
        barPos.first = 4 + pos.first + textObj->getTextSize(text.c_str()).first;
        ++barAltPos;
        ++maxBarAltPos;
    }
    else if (maxChr == -1) {
        int sz = textObj->getTextSize(text + std::string({ (char)key })).first;
        if (sz + 4 <= size.first) {
            text.insert(text.begin() + barAltPos + 1, (char)key);
            barPos.first = 4 + pos.first + sz;
            ++barAltPos;
            ++maxBarAltPos;
        }
    }
}

void pGraphics::pTextBox::checkClick() {
    if (gfx->mouseInRegion(pos, size)) {
        selected = !selected;
        if (!selected)
            function(text);
    }
    else if (selected) {
        selected = false;
        function(text);
    }
}

void pGraphics::pTextBox::onSpeciaKeyPress(int key, int action) {
    if (!selected || action == GLFW_RELEASE) return;
    int oBarPos = barPos.first;
    if (key == GLFW_KEY_ENTER) {
        selected = false;
        function(text);
    }
    else if (key == GLFW_KEY_LEFT && barAltPos >= 0)
        barPos.first -= textObj->getTextSize(std::string({ text.at(barAltPos--) })).first;
    else if (key == GLFW_KEY_RIGHT && barAltPos + 1 <= maxBarAltPos)
        barPos.first += textObj->getTextSize(std::string({ text.at(++barAltPos) })).first;
    else if (key == GLFW_KEY_BACKSPACE && text.size() >= 1 && barAltPos >= 0) {
        barPos.first -= textObj->getTextSize(std::string({ text.at(barAltPos) })).first;
        text.erase(text.begin() + barAltPos);
        --barAltPos;
        --maxBarAltPos;
    }
    else if (key == GLFW_KEY_DELETE && text.size() >= 1 && barAltPos < maxBarAltPos) {
        text.erase(text.begin() + barAltPos + 1);
        --maxBarAltPos;
    }
}

void pGraphics::pTextBox::setPos(std::pair<float, float> newPos) {
    pos = newPos;
    setText(text);
}

void pGraphics::pTextBox::setSize(std::pair<float, float> newSize) {
    size = newSize;
    barSize = { 2, size.second - 8 };
    setText(text);
}

void pGraphics::pTextBox::setText(std::string newText) {
    text = newText;
    barPos = { 4 + pos.first + textObj->getTextSize().first, 4 + pos.second };
    barSize = { 2, size.second - 8 };
    barAltPos = maxBarAltPos = -1;
    barAltPos = maxBarAltPos = newText.size() - 1;
}