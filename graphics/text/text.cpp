#include "text.hpp"

pGraphics::pText::pText(std::pair<double, double> pPos, std::string pFontLocation, int pFontSize, std::string pText, pColor pTextColor) {
    pos = pPos;
    fontLocation = pFontLocation;
    fontSize = pFontSize;
    text = pText;
    color = pTextColor;
}

pGraphics::pText::~pText() {
    glDeleteTextures(1, &atlas->id);
    atlas->id = 0;
    texture_atlas_delete(atlas);
}

void pGraphics::pText::setText(vertex_buffer_t* buffer, std::string text) {
    vec2 pen = { 0, 0 };
    float r = color.r / 255.f;
    float g = color.g / 255.f;
    float b = color.b / 255.f;
    float a = color.a / 255.f;
    for (int i = 0; i < text.size(); ++i) {
        texture_glyph_t *glyph = texture_font_get_glyph(font, std::string({ text.c_str()[i] }).c_str());
        if(glyph != NULL) {
            float kerning = 0.0f;
            if( i > 0) kerning = texture_glyph_get_kerning(glyph, std::string({ text.c_str()[i - 1] }).c_str());
            pen.x += kerning;
            int x0  = (int)(pen.x + glyph->offset_x);
            int y0  = (int)(pen.y - glyph->offset_y);
            int x1  = (int)( x0 + glyph->width );
            int y1  = (int)( y0 + glyph->height );
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint index = buffer->vertices->size;
            GLuint indices[] = {index, index+1, index+2,
                                index, index+2, index+3};
            vertex_t vertices[] = { { x0,y0,0,  s0,t0,  r,g,b,a, 0,1 },
                                    { x0,y1,0,  s0,t1,  r,g,b,a, 0,1 },
                                    { x1,y1,0,  s1,t1,  r,g,b,a, 0,1 },
                                    { x1,y0,0,  s1,t0,  r,g,b,a, 0,1 } };
            vertex_buffer_push_back_indices(buffer, indices, 6);
            vertex_buffer_push_back_vertices(buffer, vertices, 4);
            pen.x += glyph->advance_x;
        }
    }
}

void pGraphics::pText::load() {
    atlas = texture_atlas_new(512, 512, 3);
    textBuffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f,ashift:1f,agamma:1f");

    if (!fontCache[fontLocation]) {
        fontCache[fontLocation] = texture_font_new_from_file(atlas, fontSize, fontLocation.c_str());
        texture_font_load_glyphs(fontCache[fontLocation], text.c_str());
        font = fontCache[fontLocation];
    }

    setText(textBuffer, text);
    texture_font_delete(font);

    glGenTextures(1, &atlas->id);
    glBindTexture(GL_TEXTURE_2D, atlas->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlas->width, atlas->height, 0, GL_RGB, GL_UNSIGNED_BYTE, atlas->data);

    textShader = shader_load("include/freetype-gl/shaders/text.vert", "include/freetype-gl/shaders/text.frag");
}

void pGraphics::pText::draw() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, atlas->id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glColor4f( 0, 0, 0, 1 );
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    mat4_set_identity(&screen.model);
    mat4_translate(&screen.model, pos.first, pos.second, 0);
    
    glUseProgram(textShader);
    glUniform1i(glGetUniformLocation(textShader, "texture" ), 0);
    glUniform3f(glGetUniformLocation(textShader, "pixel" ), 1.f / atlas->width, 1.f / atlas->height, atlas->depth);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "model" ), 1, 0, screen.model.data);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "view" ), 1, 0, screen.view.data);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "projection" ), 1, 0, screen.projection.data);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "projection" ), 1, 0, screen.projection.data);
    vertex_buffer_render(textBuffer, GL_TRIANGLES);
    
    glDisable(GL_TEXTURE_2D);
    glUseProgram(0);
}