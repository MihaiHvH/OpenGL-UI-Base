#pragma once

#include "../../main.hpp"
#include <freetype-gl/vertex-buffer.h>
#include <freetype-gl/mat4.h>

inline std::unordered_map<std::string, texture_font_t*> fontCache;
inline const char* textCache = " !\"#$%&'()*+,-./0123456789:;<=>?"
                         "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                         "`abcdefghijklmnopqrstuvwxyz{|}~";
inline texture_atlas_t* globalAtlas = nullptr;

inline const char* vertexShader =
"uniform sampler2D tex;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
"attribute vec3 vertex;"
"attribute vec4 color;"
"attribute vec2 tex_coord;"
"varying vec4 vcolor;"
"varying vec2 vtex_coord;"
"void main() {"
"    vcolor = color;"
"    vtex_coord = tex_coord;"
"    gl_Position = projection*(view*(model*vec4(vertex,1.0)));"
"}";

inline const char* fragmentShader =
"uniform sampler2D tex;"
"varying vec4 vcolor;"
"varying vec2 vtex_coord;"
"void main() {"
"    float a = texture2D(tex, vtex_coord).r;"
"    gl_FragColor = vec4(vcolor.rgb, vcolor.a * a);"
"}";

class pGraphics::pText : public pGraphics::pElement {
    private:
        std::string fontLocation;
        int fontSize;
        std::string text;
        colors::pColor color;
        texture_font_t* font;

        GLuint textShader;
        texture_atlas_t* atlas;
        vertex_buffer_t* textBuffer;
        struct vertex_t {
            float x, y, z;
            float u, v;
            float r, g, b, a;
            float shift, gamma;
        };

        void addText(vertex_buffer_t* buffer, std::string text);
    public:
        pText(pGraphics* gfx, std::pair<float, float> pos, std::string fontLocation, int fontSize, std::string text, colors::pColor textColor);
        ~pText();

        void draw();
        void load();
               
        void setText(std::string newText);
        void setFont(std::string newFontLocation, int newFontSize);
        void setPos(std::pair<float, float> newPos) { pos = newPos; }
        void setColor(colors::pColor newColor) { color = newColor; }
        
        std::pair<float, float> getTextSize(std::string pText = "");
        std::pair<float, float> getPos() { return pos; };
        std::string getText() { return text; };
        std::pair<std::string, int> getFont() { return { fontLocation, fontSize }; };
        colors::pColor getColor() { return color; };
};