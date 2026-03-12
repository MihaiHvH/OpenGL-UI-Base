#include "slider.hpp"

pGraphics::pSlider::~pSlider() {
    
}

pGraphics::pSlider::pSlider(std::pair<double, double> pPos, std::pair<double, double> pSize, std::pair<double, double> pMinMax, int pPrecision, bool pReal, void *pFont, bool pTextPos, std::string pText, pColor pOnColor, pColor pOffColor, pColor pOutlineColor, pColor pValueTextColor, pColor pTextColor, void(*pOnValueChange)(double value)) {
    pos = pPos;
    size = pSize;
    minMax = pMinMax;
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
    onValueChange = pOnValueChange;

    value = minMax.first;
    pxOn = 0;
    pxOff = size.first - 4;
    
    if (real || (!real && precision == -1)) {
        value = real ? std::round(value) : value;
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

void pGraphics::pSlider::draw() {
    this->drawRectangle(pos, size, outlineColor);
    this->drawRectangle({ pos.first + 2, pos.second + 2}, { (int)pxOn, size.second - 4 }, onColor);
    this->drawRectangle({ pos.first + (int)pxOn + 2, pos.second + 2 }, { (int)pxOff, size.second - 4 }, offColor);

    std::pair<int, int> sz = this->getTextSize(valueText.c_str(), font);
    this->drawText({ pos.first + 2 + (int)pxOn - sz.first / 2, pos.second + sz.second / 2 + size.second / 2 }, font, valueText.c_str(), valueTextColor);

    sz = this->getTextSize(text.c_str(), font);

    if (textPos) //right
        this->drawText({ pos.first + size.first + 10, pos.second + size.second / 2 + sz.second / 2 }, font, text.c_str(), textColor);
    else //left
        this->drawText({ pos.first - sz.first - 10, pos.second + size.second / 2 + sz.second / 2 }, font, text.c_str(), textColor);
}

void pGraphics::pSlider::handleMouse() {
    if (this->mouseInRegion({ pos.first + 2, pos.second + 2 }, { size.first - 4, size.second - 4 }) && (!screen.leftClickDrag || !screen.leftClick)) {
        pxOn = screen.mousePointer.first - pos.first - 2;
        pxOff = size.first - pxOn - 4;
        value = (((pxOn * (minMax.second - minMax.first)) / (size.first - 4)) + minMax.first);
        
        std::string oldValueText = valueText;

        if (real || (!real && precision == -1)) {
            value = real ? std::round(value) : value;
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
        if (oldValueText != valueText) {
            onValueChange(value);
            screen.render();
        }
    }
}

void pGraphics::pSlider::setPos(std::pair<double, double> newPos) {
    pos = newPos;
}

void pGraphics::pSlider::setSize(std::pair<double, double> newSize) {
    size = newSize;
    double maxPxOn = size.first - 4;
    if (pxOn > maxPxOn) pxOn = maxPxOn;
    if (pxOn < 0) pxOn = 0;
    pxOff = size.first - pxOn - 4;
}

void pGraphics::pSlider::setMinMax(std::pair<double, double> newMinMax) {
    minMax = newMinMax;
    if (value < minMax.first) value = minMax.first;
    if (value > minMax.second) value = minMax.second;
    pxOn = ((value - minMax.first) / (minMax.second - minMax.first)) * (size.first - 4);
    pxOff = size.first - pxOn - 4;
}

void pGraphics::pSlider::setPrecision(int newPrecision) {
    precision = newPrecision;
    // Recalculate valueText with new precision
    if (real || (!real && precision == -1)) {
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
    }
}

void pGraphics::pSlider::setReal(bool newReal) {
    real = newReal;
    if (real || (!real && precision == -1)) {
        double tempValue = real ? std::round(value) : value;
        std::string str = std::to_string(tempValue);
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
    }
}

void pGraphics::pSlider::setFont(void *newFont) {
    font = newFont;
}

void pGraphics::pSlider::setTextPos(bool newTextPos) {
    textPos = newTextPos;
}

void pGraphics::pSlider::setText(std::string newText) {
    text = newText;
}

void pGraphics::pSlider::setOnColor(pColor newOnColor) {
    onColor = newOnColor;
}

void pGraphics::pSlider::setOffColor(pColor newOffColor) {
    offColor = newOffColor;
}

void pGraphics::pSlider::setOutlineColor(pColor newOutlineColor) {
    outlineColor = newOutlineColor;
}

void pGraphics::pSlider::setValueTextColor(pColor newValueTextColor) {
    valueTextColor = newValueTextColor;
}

void pGraphics::pSlider::setTextColor(pColor newTextColor) {
    textColor = newTextColor;
}

void pGraphics::pSlider::setFunction(void(*newOnValueChange)(double)) {
    onValueChange = newOnValueChange;
}

void pGraphics::pSlider::setValue(double newValue) {
    if (newValue < minMax.first) newValue = minMax.first;
    if (newValue > minMax.second) newValue = minMax.second;
    value = newValue;
    pxOn = ((value - minMax.first) / (minMax.second - minMax.first)) * (size.first - 4);
    pxOff = size.first - pxOn - 4;
    if (real || (!real && precision == -1)) {
        double tempValue = real ? std::round(value) : value;
        std::string str = std::to_string(tempValue);
        if (str.find('.') != std::string::npos) {
            str = str.substr(0, str.find_last_not_of('0') + 1);
            if (str.find('.') == str.size() - 1)
                str = str.substr(0, str.size() - 1);
        }
        valueText = str;
    }
    else {
        const double multiplier = std::pow(10.0, precision);
        double tempValue = std::ceil(value * multiplier) / multiplier;
        valueText = std::to_string(tempValue);
        if(valueText.find('.') != std::string::npos) {
            valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
            if (valueText.find('.') == valueText.size() - 1)
                valueText = valueText.substr(0, valueText.size() - 1);
        }
    }
}

double pGraphics::pSlider::getValue() {
    return value;
}