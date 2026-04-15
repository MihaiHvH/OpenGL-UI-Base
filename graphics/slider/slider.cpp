#include "slider.hpp"

pGraphics::pSlider::~pSlider() {
    delete valueTextObj;
}

pGraphics::pSlider::pSlider(pGraphics* pGfx, std::pair<float, float> pPos, std::pair<float, float> pSize, std::pair<float, float> pMinMax, int pDecimals, std::string pFontLocation, int pValueTextSize, pColor pOnColor, pColor pOffColor, pColor pValueTextColor, void(*pFunction)(float value)) {
    this->gfx = pGfx;
    pos = pPos;
    size = pSize;
    minMax = pMinMax;
    decimals = pDecimals;
    valueTextSize = pValueTextSize;
    onColor = pOnColor;
    offColor = pOffColor;
    function = pFunction;

    value = minMax.first;
    pxOn = 0;
    pxOff = size.first;
    
    if (decimals == -1) {
        std::string str = std::to_string(value);
        if (str.find('.') != std::string::npos) {
            str = str.substr(0, str.find_last_not_of('0') + 1);
            if (str.find('.') == str.size() - 1)
                str = str.substr(0, str.size() - 1);
        }
        valueText = str;
    }
    else {
        const float multiplier = std::pow(10.0, decimals);
        valueText = std::to_string(std::ceil(value * multiplier) / multiplier);
        if(valueText.find('.') != std::string::npos) {
            valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
            if (valueText.find('.') == valueText.size() - 1)
                valueText = valueText.substr(0, valueText.size() - 1);
        }
        value = std::ceil(value * multiplier) / multiplier;
    }

    valueTextObj = new pGraphics::pText({ 0, 0 }, pFontLocation, valueTextSize, valueText, pValueTextColor);
}

void pGraphics::pSlider::init() {
    valueTextObj->load();
}

void pGraphics::pSlider::draw() {
    gfx->drawRectangle(pos, { pxOn, size.second }, onColor);
    gfx->drawRectangle({ pos.first + pxOn, pos.second }, { pxOff, size.second }, offColor);

    std::pair<float, float> textSize = valueTextObj->getTextSize();
    valueTextObj->setText(valueText);
    valueTextObj->setPos({ pos.first + pxOn - textSize.first / 2, pos.second + (size.second + textSize.second) / 2 });
    valueTextObj->draw();
}

void pGraphics::pSlider::handleMouse() {
    if (gfx->mouseInRegion(pos, size)) {
        pxOn = screen.mousePointer.first - pos.first;
        pxOff = size.first - pxOn;
        value = (((pxOn * (minMax.second - minMax.first)) / size.first) + minMax.first);
        std::string oldValueText = valueText;

        if (decimals == -1) {
            std::string str = std::to_string(value);
            if (str.find('.') != std::string::npos) {
                str = str.substr(0, str.find_last_not_of('0') + 1);
                if (str.find('.') == str.size() - 1)
                    str = str.substr(0, str.size() - 1);
            }
            valueText = str;
        }
        else {
            const float multiplier = std::pow(10.0, decimals);
            valueText = std::to_string(std::ceil(value * multiplier) / multiplier);
            if(valueText.find('.') != std::string::npos) {
                valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
                if (valueText.find('.') == valueText.size() - 1)
                    valueText = valueText.substr(0, valueText.size() - 1);
            }
            value = std::ceil(value * multiplier) / multiplier;
        }
        if (oldValueText != valueText) {
            function(value);
            screen.render();
        }
    }
}

void pGraphics::pSlider::setPos(std::pair<float, float> newPos) {
    pos = newPos;
    std::pair<float, float> valTextSize = valueTextObj->getTextSize();
    valueTextObj->setPos({ 
        pos.first + pxOn - valTextSize.first / 2, 
        pos.second + (valTextSize.second + size.second) / 2
    });
}

void pGraphics::pSlider::setSize(std::pair<float, float> newSize) {
    size = newSize;
    float maxPxOn = size.first;
    if (pxOn > maxPxOn) pxOn = maxPxOn;
    if (pxOn < 0) pxOn = 0;
    pxOff = size.first - pxOn;
}

void pGraphics::pSlider::setMinMax(std::pair<float, float> newMinMax) {
    minMax = newMinMax;
    if (value < minMax.first) value = minMax.first;
    if (value > minMax.second) value = minMax.second;
    pxOn = ((value - minMax.first) / (minMax.second - minMax.first)) * size.first;
    pxOff = size.first - pxOn;
}

void pGraphics::pSlider::setDecimals(int newDecimals) {
    decimals = newDecimals;
    // Recalculate valueText with new precision
    if (decimals == -1) {
        std::string str = std::to_string(value);
        if (str.find('.') != std::string::npos) {
            str = str.substr(0, str.find_last_not_of('0') + 1);
            if (str.find('.') == str.size() - 1)
                str = str.substr(0, str.size() - 1);
        }
        valueText = str;
    }
    else {
        const float multiplier = std::pow(10.0, decimals);
        valueText = std::to_string(std::ceil(value * multiplier) / multiplier);
        if(valueText.find('.') != std::string::npos) {
            valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
            if (valueText.find('.') == valueText.size() - 1)
                valueText = valueText.substr(0, valueText.size() - 1);
        }
    }
}

void pGraphics::pSlider::setValue(float newValue) {
    if (newValue < minMax.first) newValue = minMax.first;
    if (newValue > minMax.second) newValue = minMax.second;
    value = newValue;
    pxOn = ((value - minMax.first) / (minMax.second - minMax.first)) * size.first;
    pxOff = size.first - pxOn;
    if (decimals == -1) {
        std::string str = std::to_string(value);
        if (str.find('.') != std::string::npos) {
            str = str.substr(0, str.find_last_not_of('0') + 1);
            if (str.find('.') == str.size() - 1)
                str = str.substr(0, str.size() - 1);
        }
        valueText = str;
    }
    else {
        const float multiplier = std::pow(10.0, decimals);
        float tempValue = std::ceil(value * multiplier) / multiplier;
        valueText = std::to_string(tempValue);
        if(valueText.find('.') != std::string::npos) {
            valueText = valueText.substr(0, valueText.find_last_not_of('0') + 1);
            if (valueText.find('.') == valueText.size() - 1)
                valueText = valueText.substr(0, valueText.size() - 1);
        }
    }
}