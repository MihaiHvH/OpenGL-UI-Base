#include "../main.hpp"

pGraphics::pGraphics() {
    black =  createNewColor(0, 0, 0);
    white =  createNewColor(255, 255,255);
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

bool pGraphics::mouseInRegion(std::pair<double, double> pos, std::pair<double, double> size) {
    return screen.mousePointer.first >= pos.first &&
           screen.mousePointer.first <= pos.first + size.first &&
           screen.mousePointer.second >= pos.second &&
           screen.mousePointer.second <= pos.second + size.second;
}

void pGraphics::drawPolygon(std::vector<std::pair<double, double>> points, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    for (std::pair<double, double> point : points)
        glVertex2d(point.first, point.second);
    glEnd();
}

void pGraphics::drawRectangle(std::pair<double, double> pos, std::pair<double, double> size, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    glVertex2d(pos.first, pos.second); //corner down
    glVertex2d(pos.first + size.first, pos.second); //right down corner
    glVertex2d(pos.first + size.first, pos.second + size.second); //right up corner
    glVertex2d(pos.first, pos.second + size.second); //corner up
    glEnd();
}

void pGraphics::drawFilledCircle(std::pair<double, double> centrePos, double r, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    for (double i = 0; i <= 100; ++i) {
        double angle = M_PI * i / 50;
        double x = cos(angle) * r;
        double y = sin(angle) * r;
        glVertex2d(centrePos.first + x, centrePos.second + y);
    }
    glEnd();
}

void pGraphics::drawOutlinedCircle(std::pair<double, double> centrePos, double r, double lineThickness, pColor color) {
    double inner = r - lineThickness * 0.5;
    double outer = r + lineThickness * 0.5;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= 100; ++i) {
        double angle = M_PI * i / 50;
        double x = cos(angle);
        double y = sin(angle);
        glVertex2d(centrePos.first + x * outer, centrePos.second + y * outer);
        glVertex2d(centrePos.first + x * inner, centrePos.second + y * inner);
    }
    glEnd();
}

void pGraphics::drawTriangle(std::pair<double, double> points[3], pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_TRIANGLES);
    glVertex2d(points[0].first, points[0].second);
    glVertex2d(points[1].first, points[1].second);
    glVertex2d(points[2].first, points[2].second);
    glEnd();
}

void pGraphics::drawFilledEllipse(std::pair<double, double> pos, std::pair<double, double> size, pColor color) { 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    float angle = M_PI / 50; 
    float c = cosf(angle);
    float s = sinf(angle);
    float t, x = 1, y = 0;
    for(int i = 0; i <= 100; ++i)  { 
        glVertex2d(x * size.first + pos.first, y * size.second + pos.second);//output vertex 
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 
    glEnd(); 
}

void pGraphics::drawOutlinedEllipse(std::pair<double, double> pos, std::pair<double, double> size, double lineThickness, pColor color) { 
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
    onResize(screen.initialSize.first, screen.initialSize.second);
}