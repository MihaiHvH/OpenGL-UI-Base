#include "slider.hpp"

pGraphics::pSlider::~pSlider() {
    
}

pGraphics::pSlider::pSlider(std::pair<int, int> pPos, std::pair<int, int> pSize, std::pair<double, double> pMin_max, int pPrecision, bool pReal, void *pFont, bool pTextPos, std::string pText, pColor pOnColor, pColor pOffColor, pColor pOutlineColor, pColor pValueTextColor, pColor pTextColor, void(*pRender)(void), void(*pOnValueChange)(double value)) {
    pos = pPos;
    size = pSize;
    min_max.first = pMin_max.first;
    min_max.second = pMin_max.second;
    precision = pPrecision;
    real = pReal;
    font = pFont;
    textPos = pTextPos;
    text = pText;
    onColor = pOnColor;
    offColor = pOffColor;
    outlineColor = pOutlineColor;
    valueTextColor = pValueTextColor;
    textColor = pTextColor;
    render = pRender;
    onValueChange = pOnValueChange;

    value = min_max.first;
    pxOn = 0;
    pxOff = size.first - 4;
    
    if (real) {
            value = std::round(value);
            std::string str = std::to_string(value);
            if (str.find('.') != std::string::npos) {
                str = str.substr(0, str.find_last_not_of('0')+1);
                if (str.find('.') == str.size() - 1)
                    str = str.substr(0, str.size() - 1);
            }
            valueText = str;
        }
    if (!real) {
        if (precision == -1) {
            std::string str = std::to_string(value);
            if (str.find('.') != std::string::npos) {
                str = str.substr(0, str.find_last_not_of('0') + 1);
                if (str.find('.') == str.size() - 1)
                    str = str.substr(0, str.size() - 1);
            }
            valueText = str;
        }
        else {
            const double multiplier = std::pow(10.0, precision);
            valueText = std::to_string(std::ceil(value * multiplier) / multiplier);
            if(valueText.find('.') != std::string::npos) {
                valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
                if(valueText.find('.') == valueText.size() - 1)
                    valueText = valueText.substr(0, valueText.size() - 1);
            }
            value = std::ceil(value * multiplier) / multiplier;
        }
    }
}

void pGraphics::pSlider::draw(pInterface interface) {
    interface.graphics.drawRect(pos, size, outlineColor);
    interface.graphics.drawRect({ pos.first + 2, pos.second + 2}, { (int)pxOn, size.second - 4 }, onColor);
    interface.graphics.drawRect({ pos.first + (int)pxOn + 2, pos.second + 2 }, { (int)pxOff, size.second - 4 }, offColor);

    const unsigned char* str = reinterpret_cast<const unsigned char*>(valueText.c_str());
    std::pair<int, int> sz = { glutBitmapLength(font, str), glutBitmapWidth(font, valueText[0])};

    interface.graphics.drawText({ pos.first + 2 + (int)pxOn - sz.first / 2, pos.second + sz.second / 2 + size.second / 2 }, font, valueText.c_str(), valueTextColor);

    str = reinterpret_cast<const unsigned char*>(text.c_str());
    sz = { glutBitmapLength(font, str), glutBitmapWidth(font, text[0])};

    //if right
    if (textPos)
        interface.graphics.drawText({ pos.first + size.first + 10, pos.second + size.second / 2 + sz.second / 2 }, font, text.c_str(), textColor);
    //else left
    else
        interface.graphics.drawText({ pos.first - sz.first - 10, pos.second + size.second / 2 + sz.second / 2 }, font, text.c_str(), textColor);
}

void pGraphics::pSlider::handleMouse(pInterface interface) {
    if (interface.graphics.mouseInRegion(interface.screen.mousePointer, { pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }) && (!interface.screen.leftClickDrag || !interface.screen.leftClick)) {
        pxOn = interface.screen.mousePointer.first - pos.first - 2;
        pxOff = size.first - pxOn - 4;
        value = (((pxOn * (min_max.second - min_max.first)) / (size.first - 4)) + min_max.first);
        
        if (real) {
            value = std::round(value);
            std::string str = std::to_string(value);
            if (str.find('.') != std::string::npos) {
                str = str.substr(0, str.find_last_not_of('0') + 1);
                if (str.find('.') == str.size() - 1)
                    str = str.substr(0, str.size() - 1);
            }
            valueText = str;
        }
        if (!real) {
            if (precision == -1) {
                std::string str = std::to_string(value);
                if (str.find('.') != std::string::npos) {
                    str = str.substr(0, str.find_last_not_of('0') + 1);
                    if (str.find('.') == str.size() - 1)
                        str = str.substr(0, str.size() - 1);
                }
                valueText = str;
            }
            else {
                const double multiplier = std::pow(10.0, precision);
                valueText = std::to_string(std::ceil(value * multiplier) / multiplier);
                if(valueText.find('.') != std::string::npos) {
                    valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
                    if (valueText.find('.') == valueText.size() - 1)
                        valueText = valueText.substr(0, valueText.size() - 1);
                }
                value = std::ceil(value * multiplier) / multiplier;
            }
        }
        onValueChange(value);
    }
    render();
}