#include "../main.hpp"
#include "graphics.hpp"

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
    pColor color;
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

bool pGraphics::mouseInRegion(std::pair<int, int> mousePointer, std::pair<int, int> pos, std::pair<int, int> size) {
    if (mousePointer.first >= pos.first &&
        mousePointer.first <= pos.first + size.first &&
        mousePointer.second >= pos.second &&
        mousePointer.second <= pos.second + size.second)
        return true;
    return false;
}

void pGraphics::drawRect(std::pair<int, int> pos, std::pair<int, int> size, pColor color) {
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    glVertex2f(pos.first, pos.second); //corner down
    glVertex2f(pos.first + size.first, pos.second); //right down corner
    glVertex2f(pos.first + size.first, pos.second + size.second); //right up corner
    glVertex2f(pos.first, pos.second + size.second); //corner up
    glEnd();
}

void pGraphics::drawFilledCircle(std::pair<int, int> pos, double r, pColor color) {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    glBegin(GL_POLYGON);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    for (double i = 0; i <= 360;) {
        double angle = 2 * M_PI * i / 360;
        double x = cos(angle) * r;
        double y = sin(angle) * r;
        glVertex2d(pos.first + x, pos.second + y);
        i += 0.25;
    }
    glEnd();
}

void pGraphics::drawTriangle(std::pair<int, int> point1, std::pair<int, int> point2, std::pair<int, int> point3, pColor color) {
    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_TRIANGLES);
    glVertex2d(point1.first, point1.second);
    glVertex2d(point2.first, point2.second);
    glVertex2d(point3.first, point3.second);
    glEnd();
}

void pGraphics::drawText(std::pair<int, int> pos, void *font, const char *str, pColor color) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glRasterPos2f(pos.first, pos.second);
    
    for (int i = 0; i < strlen(str); ++i)
        glutBitmapCharacter(font, str[i]);
}