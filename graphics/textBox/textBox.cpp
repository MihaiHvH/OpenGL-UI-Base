#include "textBox.hpp"
#include <cstring>
#include <string>

pGraphics::pTextBox::~pTextBox() {
    
}

pGraphics::pTextBox::pTextBox(std::pair<double, double> pPos, std::pair<double, double> pSize, int pMaxChr, std::string pFontLocation, int pFontSize, pColor pOutlineColor, pColor pInsideColor, pColor pBarColor, pColor pTextColor, void(*pOnEnter)(std::string text)) {
    pos = pPos;
    size = pSize;
    maxChr = pMaxChr;
    fontLocation = pFontLocation;
    fontSize = pFontSize;
    outlineColor = pOutlineColor;
    insideColor = pInsideColor;
    barColor = pBarColor;
    onEnter = pOnEnter;
    textColor = pTextColor;

    barPos = { 6 + pPos.first, 4 + pPos.second };
    barSize = { 2, pSize.second - 8 };

    barX = barPos.first;

    textObj = new pGraphics::pText({ 0, 0 }, fontLocation, fontSize, text, textColor);
}

void pGraphics::pTextBox::draw() {
    this->drawRectangle(pos, size, outlineColor);
    this->drawRectangle({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }, insideColor);
    
    double textHeight = textObj->getTextSize().second;
    textObj->setPos({ pos.first + 6, pos.second + (size.second / 2) + textHeight / 2 + 2 });
    textObj->setText(text);
    textObj->draw();

    if (selected) this->drawRectangle(barPos, barSize, barColor);
}

void pGraphics::pTextBox::init() {
    textObj->load();
}

void pGraphics::pTextBox::onKeyPress(unsigned int key) {
    if (!selected) return;
    if (maxBarAltPos + 2 <= maxChr && maxChr != -1) {
        text.insert(text.begin() + barAltPos + 1, (char)key);
        barPos.first = barX + textObj->getTextSize(text.c_str()).first;
        ++barAltPos;
        ++maxBarAltPos;
    }
    else if (maxChr == -1) {
        int sz = textObj->getTextSize(text + std::string({ (char)key })).first;
        if (sz + 8 <= size.first) {
            text.insert(text.begin() + barAltPos + 1, (char)key);
            barPos.first = barX + sz;
            ++barAltPos;
            ++maxBarAltPos;
        }
    }
    screen.render();
}

void pGraphics::pTextBox::checkClick() {
    if (this->mouseInRegion(pos, size)) {
        selected = !selected;
        screen.render();
        if (!selected)
            onEnter(text);
    }
    else if (selected) {
        selected = false;
        screen.render();
        onEnter(text);
    }
}

void pGraphics::pTextBox::onSpeciaKeyPress(int key, int action) {
    if (!selected || action == GLFW_RELEASE) return;
    int oBarPos = barPos.first;
    if (key == GLFW_KEY_ENTER) {
        selected = false;
        onEnter(text);
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
    // TO DO
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
    /*for (unsigned int i = 0; i < newText.size(); ++i) {
        barPos.first += this->getTextSize(std::string({ newText.at(i) }), font).first;
        ++barAltPos;
        ++maxBarAltPos;
    }*/
    barPos.first = textObj->getTextSize(newText).first;
    barAltPos = newText.size();
    maxBarAltPos = newText.size();
}

std::string pGraphics::pTextBox::getText() {
    return text;
}