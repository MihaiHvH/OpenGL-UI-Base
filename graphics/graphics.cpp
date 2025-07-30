#include "../main.hpp"
#include <GL/gl.h>
#include "graphics.hpp"

#ifndef M_PI
    #define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
#endif

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
    pColor color{};
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

bool pGraphics::mouseInRegion(std::pair<double, double> pos, std::pair<double, double> size) {
    return screen.mousePointer.first >= pos.first &&
           screen.mousePointer.first <= pos.first + size.first &&
           screen.mousePointer.second >= pos.second &&
           screen.mousePointer.second <= pos.second + size.second;
}

void pGraphics::draw4PointRect(std::pair<double, double> points[4], pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glBegin(GL_POLYGON);
    glVertex2d(points[0].first, points[0].second);
    glVertex2d(points[1].first, points[1].second);
    glVertex2d(points[2].first, points[2].second);
    glVertex2d(points[3].first, points[3].second);
    glEnd();
}

void pGraphics::drawRect(std::pair<double, double> pos, std::pair<double, double> size, pColor color) {
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
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_POLYGON);
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    for (double i = 0; i <= 360;) {
        double angle = 2 * M_PI * i / 360;
        double x = cos(angle) * r;
        double y = sin(angle) * r;
        glVertex2d(centrePos.first + x, centrePos.second + y);
        i += 0.25;
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

std::pair<int, int> pGraphics::getTextSize(const char* str, void* font) {
    int wMax = -1;
    for (size_t i = 0; i < strlen(str); ++i)
        wMax = std::max(wMax, glutBitmapWidth(font, str[i]));
    return { glutBitmapLength(font, reinterpret_cast<const unsigned char*>(str)), wMax };
}

void pGraphics::drawText(std::pair<double, double> pos, void *font, const char *str, pColor color) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor4f(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
    glRasterPos2d(pos.first, pos.second);
    
    for (size_t i = 0; i < strlen(str); ++i)
        glutBitmapCharacter(font, str[i]);
}