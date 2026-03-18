#pragma once

#include "../../main.hpp"
#include <freetype-gl/vertex-buffer.h>
#include <freetype-gl/mat4.h>

inline std::unordered_map<std::string, texture_font_t*> fontCache;
inline const char* textCache = " !\"#$%&'()*+,-./0123456789:;<=>?"
                         "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                         "`abcdefghijklmnopqrstuvwxyz{|}~";
inline texture_atlas_t* globalAtlas = nullptr;

class pGraphics::pText : public pGraphics {
    private:
        std::pair<double, double> pos;
        std::pair<double, double> size = { 0, 0 };
        std::string fontLocation;
        int fontSize;
        std::string text;
        pColor color;
        texture_font_t *font;

        GLuint textShader;
        texture_atlas_t* atlas;
        vertex_buffer_t* textBuffer;
        typedef struct {
            float x, y, z;
            float u, v;
            float r, g, b, a;
            float shift, gamma;
        } vertex_t;

        void addText(vertex_buffer_t* buffer, std::string text);
    public:
        pText(std::pair<double, double> pPos, std::string pFontLocation, int pFontSize, std::string pText, pColor pTextColor);
        ~pText();

        void draw();
        void load();
               
        std::pair<double, double> getTextSize(std::string pText = "");

        void setText(std::string newText);
        void setPos(std::pair<double, double> newPos) { pos = newPos; }
        void setColor(pColor newColor) { color = newColor; }
};