#pragma once

#include "../../main.hpp"
#include <freetype-gl/vertex-buffer.h>
#include <freetype-gl/mat4.h>

class pGraphics::pText : public pGraphics {
    private:
        std::pair<double, double> pos;
        std::pair<int, int> size = { 0, 0 };
        std::string fontLocation;
        int fontSize;
        std::string text;
        pColor color;
        texture_font_t *font;

        GLuint textShader;
        vertex_buffer_t* textBuffer;
        
        texture_atlas_t* atlas;
        typedef struct {
            float x, y, z;
            float u, v;
            float r, g, b, a;
            float shift, gamma;
        } vertex_t;
    public:
        pText(std::pair<double, double> pPos, std::string pFontLocation, int pFontSize, std::string pText, pColor pTextColor);
        ~pText();

        void draw();
        void load();

        void setText(vertex_buffer_t* buffer, std::string text);
               
        std::pair<int, int> getTextSize();

        void setText(std::string newText) { text = newText; }
        void setPos(std::pair<double, double> newPos) { pos = newPos; }
        void setColor(pColor newColor) { color = newColor; }
};