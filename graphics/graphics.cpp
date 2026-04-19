#include "../main.hpp"

pGraphics::pGraphics() {

}

pGraphics::~pGraphics() {

}

bool pGraphics::mouseInRegion(std::pair<float, float> pos, std::pair<float, float> size) {
    return screen.mousePointer.first >= pos.first &&
           screen.mousePointer.first <= pos.first + size.first &&
           screen.mousePointer.second >= pos.second &&
           screen.mousePointer.second <= pos.second + size.second;
}

void pGraphics::drawPolygon(std::vector<std::pair<float, float>> points, colors::pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    for (std::pair<float, float> point : points)
        glVertex2d(point.first, point.second);
    glEnd();
}

void pGraphics::drawRectangle(std::pair<float, float> pos, std::pair<float, float> size, colors::pColor color) {
    drawPolygon({ { pos.first, pos.second }, { pos.first + size.first, pos.second }, { pos.first + size.first, pos.second + size.second}, { pos.first, pos.second + size.second } }, color);
}

void pGraphics::drawFilledCircle(std::pair<float, float> centrePos, float r, colors::pColor color) {
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

void pGraphics::drawOutlinedCircle(std::pair<float, float> centrePos, float r, float lineThickness, colors::pColor color) {
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

void pGraphics::drawTriangle(std::pair<float, float> points[3], colors::pColor color) {
    drawPolygon({ points[0], points[1], points[2] }, color);
}

void pGraphics::drawFilledEllipse(std::pair<float, float> pos, std::pair<float, float> size, colors::pColor color) { 
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

void pGraphics::drawOutlinedEllipse(std::pair<float, float> pos, std::pair<float, float> size, float lineThickness, colors::pColor color) { 
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
    size = { newWidth, newHeight };
    mat4_set_orthographic(&projection, 0, newWidth, newHeight, 0, -1, 1);
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, newWidth, newHeight, 0, -1, 1);
}

void pGraphics::init() {
    if (isInit)
        return;

    mat4_set_identity(&projection);
    mat4_set_identity(&model);
    mat4_set_identity(&view);
    onResize(size.first, size.second);

    for (auto const& [name, slider] : sliders)
        slider->init();
    for (auto const& [name, textBox] : textBoxes)
        textBox->init();
    for (auto const& [name, text] : texts)
        text->load();

    ilInit();

    for (auto const& [name, image] : images)
        image->load();

    isInit = true;
}

void pGraphics::processSpecialInput(int key, int scancode, int action, int mods) {
    for (auto const& [name, textBox] : textBoxes)
        if (textBox->enabled)
            textBox->onSpeciaKeyPress(key, action);
}

void pGraphics::processInput(unsigned int key) {
    for (auto const& [name, textBox] : textBoxes)
        if (textBox->enabled)
            textBox->onKeyPress(key);
}

void pGraphics::handleMouseKeys(int button, int action, int mods) {
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

void pGraphics::handleMouseMovement(int x, int y) {
    screen.mousePointer = { x, y };
    if (screen.leftClick == GLFW_PRESS) handleMouseDrag(x, y);
}

void pGraphics::handleMouseDrag(int x, int y) {
    for (auto const& [name, slider] : sliders)
        if (slider->enabled)
            slider->handleMouse();
}