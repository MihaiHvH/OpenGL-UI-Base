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

    for (auto const& [name, slider] : sliders)
        slider->init();
    for (auto const& [name, textBox] : textBoxes)
        textBox->init();
    for (auto const& [name, text] : texts)
        text->load();

    if (!images.empty())
        ilInit();

    for (auto const& [name, image] : images)
        image->load();
}

pGraphics::pButton* pGraphics::createButton(std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::vector<pColor> colors, void(*function)(int)) {
    if (buttons.find(name) != buttons.end())
        throw std::runtime_error("[createButton] Error: You can't name two buttons the same!");
    pButton* button = new pGraphics::pButton(this, pos, size, colors, function);
    buttons[name] = button;
    return buttons.at(name);
}

pGraphics::pImage* pGraphics::createImage(std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::string imageLocation, std::string altText, std::string fontLocation) {
    if (images.find(name) != images.end())
        throw std::runtime_error("[createImage] Error: You can't name two images the same!");
    pImage* image = new pGraphics::pImage(this, pos, size, imageLocation, altText, fontLocation);
    images[name] = image;
    return images.at(name);
}

pGraphics::pSlider* pGraphics::createSlider(std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, pColor onColor, pColor offColor, pColor valueTextColor, void(*function)(float)) {
    if (sliders.find(name) != sliders.end())
        throw std::runtime_error("[createSlider] Error: You can't name two sliders the same!");
    pSlider* slider = new pGraphics::pSlider(this, pos, size, minMax, decimals, fontLocation, valueTextSize, onColor, offColor, valueTextColor, function);
    sliders[name] = slider;
    return sliders.at(name);
}

pGraphics::pText* pGraphics::createText(std::string name, std::pair<float, float> pos, std::string fontLocation, int fontSize, std::string text, pColor textColor) {
    if (texts.find(name) != texts.end())
        throw std::runtime_error("[createText] Error: You can't name two texts the same!");
    pText* textElement = new pGraphics::pText(pos, fontLocation, fontSize, text, textColor);
    texts[name] = textElement;
    return texts.at(name);
}

pGraphics::pTextBox* pGraphics::createTextBox(std::string name, std::pair<float, float> pos, std::pair<float, float> size, int maxChr, std::string fontLocation, int fontSize, pColor insideColor, pColor barColor, pColor textColor, void(*function)(std::string)) {
    if (textBoxes.find(name) != textBoxes.end())
        throw std::runtime_error("[createTextBox] Error: You can't name two textBoxes the same!");
    pTextBox* textBox = new pGraphics::pTextBox(this, pos, size, maxChr, fontLocation, fontSize, insideColor, barColor, textColor, function);
    textBoxes[name] = textBox;
    return textBoxes.at(name);
}

void pGraphics::processSpecialInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (auto const& [name, textBox] : textBoxes)
        if (textBox->enabled)
            textBox->onSpeciaKeyPress(key, action);
}

void pGraphics::processInput(GLFWwindow* window, unsigned int key) {
    for (auto const& [name, textBox] : textBoxes)
        if (textBox->enabled)
            textBox->onKeyPress(key);
}

void pGraphics::handleMouseKeys(GLFWwindow* window, int button, int action, int mods) {
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            screen.leftClick = action;
            
            if (screen.leftClick != GLFW_PRESS)
                break;

            for (auto const& [name, button]: buttons)
                if (button->enabled)
                    button->checkClick();

            for (auto const& [name, slider]: sliders)
                if (slider->enabled)
                    slider->handleMouse();

            for (auto const& [name, textBox]: textBoxes)
                if (textBox->enabled)
                    textBox->checkClick();

            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            screen.rightClick = action;

            if (screen.rightClick != GLFW_PRESS)
                break;

            break;
        }
    }
}

void pGraphics::handleMouseMovement(GLFWwindow* window, int x, int y) {
    screen.mousePointer = { x, y };
    if (screen.leftClick == GLFW_PRESS) handleMouseDrag(window, x, y);
}

void pGraphics::handleMouseDrag(GLFWwindow* window, int x, int y) {
    for (auto const& [name, slider] : sliders)
        if (slider->enabled)
            slider->handleMouse();
}