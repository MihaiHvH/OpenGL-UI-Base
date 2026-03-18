#pragma once

#include "../../main.hpp"
#include <freetype-gl/vertex-buffer.h>
#include <freetype-gl/mat4.h>

class pGraphics::pText : public pGraphics {
    private:
        std::pair<double, double> pos;
        std::string fontLocation;
        std::string text;
        pColor color;
        
        texture_font_t* getFont(const std::string& fontPath, int fontSize);

        GLuint text_shader;
        vertex_buffer_t* text_buffer;
        mat4 projection, view, model;
        typedef struct {
            float x, y, z;
            float u, v;
            float r, g, b, a;
            float shift, gamma;
        } vertex_t;
    public:
        pText(std::pair<double, double> pPos, std::string pFontLocation, std::string pText, pColor pTextColor);
        ~pText();

        void draw();
        
        void init(int width = 512, int height = 512);
        void cleanup();
        void onResize(int width, int height);

        void add_text( vertex_buffer_t * buffer, texture_font_t * font,
               char * text, vec4 * color, vec2 * pen );
               
        std::string& getText() { return text; }
        std::pair<double, double>& getPos() { return pos; }
        std::string& getFontLocation() { return fontLocation; }
        pColor& getColor() { return color; }
        
        void setText(const std::string& newText) { text = newText; }
        void setPos(const std::pair<double, double>& newPos) { pos = newPos; }
        void setColor(const pColor& newColor) { color = newColor; }
};