#include "../main.hpp"

pGraphics::pGraphics() {
    black =  createNewColor(0, 0, 0);
    white =  createNewColor(255, 255,255);
    gray =   createNewColor(128, 128, 128);
    red =    createNewColor(255, 0, 0);
    green =  createNewColor(0, 255, 0);
    blue =   createNewColor(0, 0, 255);
    yellow = createNewColor(255, 255, 0);
    cyan =   createNewColor(0, 255, 255);
    purple = createNewColor(255, 0, 255);
}

pGraphics::~pGraphics() {

}

pColor pGraphics::createNewColor(int r, int g, int b, int a) {
    return { r, g, b, a };
}

bool pGraphics::mouseInRegion(std::pair<float, float> pos, std::pair<float, float> size) {
    return screen.mousePointer.first >= pos.first &&
           screen.mousePointer.first <= pos.first + size.first &&
           screen.mousePointer.second >= pos.second &&
           screen.mousePointer.second <= pos.second + size.second;
}

void pGraphics::drawPolygon(std::vector<std::pair<float, float>> points, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    for (std::pair<float, float> point : points)
        glVertex2d(point.first, point.second);
    glEnd();
}

void pGraphics::drawRectangle(std::pair<float, float> pos, std::pair<float, float> size, pColor color) {
    drawPolygon({ { pos.first, pos.second }, { pos.first + size.first, pos.second }, { pos.first + size.first, pos.second + size.second}, { pos.first, pos.second + size.second } }, color);
}

void pGraphics::drawFilledCircle(std::pair<float, float> centrePos, float r, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    for (float i = 0; i <= 100; ++i) {
        float angle = M_PI * i / 50;
        float x = cos(angle) * r;
        float y = sin(angle) * r;
        glVertex2d(centrePos.first + x, centrePos.second + y);
    }
    glEnd();
}

void pGraphics::drawOutlinedCircle(std::pair<float, float> centrePos, float r, float lineThickness, pColor color) {
    float inner = r - lineThickness * 0.5;
    float outer = r + lineThickness * 0.5;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        float angle = M_PI * i / 50;
        float x = cos(angle);
        float y = sin(angle);
        glVertex2d(centrePos.first + x * outer, centrePos.second + y * outer);
        glVertex2d(centrePos.first + x * inner, centrePos.second + y * inner);
    }
    glEnd();
}

void pGraphics::drawTriangle(std::pair<float, float> points[3], pColor color) {
    drawPolygon({ points[0], points[1], points[2] }, color);
}

void pGraphics::drawFilledEllipse(std::pair<float, float> pos, std::pair<float, float> size, pColor color) { 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    float angle = M_PI / 50; 
    float c = cosf(angle);
    float s = sinf(angle);
    float t, x = 1, y = 0;
    for(int i = 0; i <= 100; ++i)  { 
        glVertex2d(x * size.first + pos.first, y * size.second + pos.second);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 
    glEnd(); 
}

void pGraphics::drawOutlinedEllipse(std::pair<float, float> pos, std::pair<float, float> size, float lineThickness, pColor color) { 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_TRIANGLE_STRIP);
    float angle = M_PI / 50;
    float c = cosf(angle);
    float s = sinf(angle);
    float x = 1.0f, y = 0.0f;
    float innerX, innerY, outerX, outerY;
    for (int i = 0; i <= 100; i++) {
        outerX = (x * (size.first + lineThickness * 0.5f)) + pos.first;
        outerY = (y * (size.second + lineThickness * 0.5f)) + pos.second;
        innerX = (x * (size.first - lineThickness * 0.5f)) + pos.first;
        innerY = (y * (size.second - lineThickness * 0.5f)) + pos.second;
        glVertex2f(outerX, outerY);
        glVertex2f(innerX, innerY);
        float t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void pGraphics::onResize(int newWidth, int newHeight) {
    mat4_set_orthographic(&screen.projection, 0, newWidth, newHeight, 0, -1, 1);
}

void pGraphics::init() {
    mat4_set_identity(&screen.projection);
    mat4_set_identity(&screen.model);
    mat4_set_identity(&screen.view);
    onResize(screen.size.first, screen.size.second);
}

pGraphics::pButton* pGraphics::createButton(std::pair<float, float> pos, std::pair<float, float> size, std::vector<pColor> colors, void(*function)(int)) {
    return new pGraphics::pButton(this, pos, size, colors, function);
}

pGraphics::pImage* pGraphics::createImage(std::pair<float, float> pos, std::pair<float, float> size, std::string imageLocation, std::string altText, std::string fontLocation) {
    return new pGraphics::pImage(this, pos, size, imageLocation, altText, fontLocation);
}

pGraphics::pSlider* pGraphics::createSlider(std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, pColor onColor, pColor offColor, pColor valueTextColor, void(*function)(float)) {
    return new pGraphics::pSlider(this, pos, size, minMax, decimals, fontLocation, valueTextSize, onColor, offColor, valueTextColor, function);
}

pGraphics::pText* pGraphics::createText(std::pair<float, float> pos, std::string fontLocation, int fontSize, std::string text, pColor textColor) {
    return new pGraphics::pText(pos, fontLocation, fontSize, text, textColor);
}

pGraphics::pTextBox* pGraphics::createTextBox(std::pair<float, float> pos, std::pair<float, float> size, int maxChr, std::string fontLocation, int fontSize, pColor insideColor, pColor barColor, pColor textColor, void(*function)(std::string)) {
    return new pGraphics::pTextBox(this, pos, size, maxChr, fontLocation, fontSize, insideColor, barColor, textColor, function);
}