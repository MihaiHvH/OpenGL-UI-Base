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
"uniform vec3 pixel;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
"attribute vec3 vertex;"
"attribute vec4 color;"
"attribute vec2 tex_coord;"
"attribute float ashift;"
"attribute float agamma;"
"varying vec4 vcolor;"
"varying vec2 vtex_coord;"
"varying float vshift;"
"varying float vgamma;"
"void main() {"
"    vshift = ashift;"
"    vgamma = agamma;"
"    vcolor = color;"
"    vtex_coord = tex_coord;"
"    gl_Position = projection*(view*(model*vec4(vertex,1.0)));"
"}";

inline const char* fragmentShader =
"uniform sampler2D tex;"
"uniform vec3 pixel;"
"varying vec4 vcolor;"
"varying vec2 vtex_coord;"
"varying float vshift;"
"varying float vgamma;"
"void main() {"
"    if( pixel.z == 1.0) {"
"        float a = texture2D(tex, vtex_coord).r;"
"        gl_FragColor = vcolor * pow( a, 1.0/vgamma );"
"        return;"
"    }"
"    vec4 current = texture2D(tex, vtex_coord);"
"    vec4 previous= texture2D(tex, vtex_coord+vec2(-1.,0.)*pixel.xy);"
"    vec4 next    = texture2D(tex, vtex_coord+vec2(+1.,0.)*pixel.xy);"
"    current = pow(current, vec4(1.0/vgamma));"
"    previous= pow(previous, vec4(1.0/vgamma));"
"    float r = current.r;"
"    float g = current.g;"
"    float b = current.b;"
"    if( vshift <= 0.333 ) {"
"        float z = vshift/0.333;"
"        r = mix(current.r, previous.b, z);"
"        g = mix(current.g, current.r,  z);"
"        b = mix(current.b, current.g,  z);"
"    }"
"    else if( vshift <= 0.666 ){"
"        float z = (vshift-0.33)/0.333;"
"        r = mix(previous.b, previous.g, z);"
"        g = mix(current.r,  previous.b, z);"
"        b = mix(current.g,  current.r,  z);"
"    }"
"   else if( vshift < 1.0 ){"
"        float z = (vshift-0.66)/0.334;"
"        r = mix(previous.g, previous.r, z);"
"        g = mix(previous.b, previous.g, z);"
"        b = mix(current.r,  previous.b, z);"
"    }"
"   float t = max(max(r,g),b);"
"   vec4 color = vec4(vcolor.rgb, (r+g+b)/3.0);"
"   color = t*color + (1.0-t)*vec4(r,g,b, min(min(r,g),b));"
"   gl_FragColor = vec4( color.rgb, vcolor.a*color.a);"
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