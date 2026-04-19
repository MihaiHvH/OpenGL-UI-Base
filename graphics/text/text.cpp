#include "text.hpp"

pGraphics::pText::pText(pGraphics* pGfx, std::pair<float, float> pPos, std::string pFontLocation, int pFontSize, std::string pText, colors::pColor pTextColor) {
    gfx = pGfx;
    pos = pPos;
    fontLocation = pFontLocation;
    fontSize = pFontSize;
    text = pText;
    color = pTextColor;
}

pGraphics::pText::~pText() {
    if (textBuffer) {
        vertex_buffer_delete(textBuffer);
        textBuffer = nullptr;
    }
}

void pGraphics::pText::addText(vertex_buffer_t* buffer, std::string text) {
    vec2 pen = { 0, 0 };
    float r = color.r / 255.f;
    float g = color.g / 255.f;
    float b = color.b / 255.f;
    float a = color.a / 255.f;
    size.first = 0;
    size.second = texture_font_get_glyph(font, "H")->height;
    for (int i = 0; i < text.size(); ++i) {
        texture_glyph_t* glyph = texture_font_get_glyph(font, std::string({ text.c_str()[i] }).c_str());
        if (glyph != NULL) {
            if (i == text.size() - 1) size.first += glyph->offset_x + glyph->width;
            else size.first += glyph->advance_x;
            float kerning = 0.0f;
            if (i > 0) kerning = texture_glyph_get_kerning(glyph, std::string({ text.c_str()[i - 1] }).c_str());
            pen.x += kerning;
            float x0  = floor(pen.x + glyph->offset_x);
            float y0  = floor(pen.y - glyph->offset_y);
            float x1  = x0 + glyph->width;
            float y1  = y0 + glyph->height;
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint index = buffer->vertices->size;
            GLuint indices[] = { index, index + 1, index + 2,
                                index, index + 2, index + 3 };
            vertex_t vertices[] = { { x0, y0 , 0,  s0, t0,  r, g, b, a, 0, 1.f },
                                    { x0, y1 , 0,  s0, t1,  r, g, b, a, 0, 1.f },
                                    { x1, y1 , 0,  s1, t1,  r, g, b, a, 0, 1.f },
                                    { x1, y0 , 0,  s1, t0,  r, g, b, a, 0, 1.f } };
            vertex_buffer_push_back_indices(buffer, indices, 6);
            vertex_buffer_push_back_vertices(buffer, vertices, 4);
            pen.x += glyph->advance_x;
        }
    }
}

void pGraphics::pText::load() {
    if (!globalAtlas) {
        globalAtlas = texture_atlas_new(512, 512, 3);
        glGenTextures(1, &globalAtlas->id);
    }
    textBuffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f,ashift:1f,agamma:1f");
    atlas = globalAtlas;

    setFont(fontLocation, fontSize);

    glBindTexture(GL_TEXTURE_2D, atlas->id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, atlas->width, atlas->height, 0, GL_RGB, GL_UNSIGNED_BYTE, atlas->data);

    textShader = shader_load_from_string(vertexShader, fragmentShader);
}

void pGraphics::pText::setFont(std::string newFontLocation, int newFontSize) {
    std::string cacheKey = newFontLocation + "@" + std::to_string(newFontSize);

    if (fontCache.find(cacheKey) == fontCache.end()) {
        fontCache[cacheKey] = texture_font_new_from_file(atlas, newFontSize, newFontLocation.c_str());
        texture_font_load_glyphs(fontCache[cacheKey], textCache);
    }

    font = fontCache[cacheKey];

    setText(text);
}

void pGraphics::pText::setText(std::string newText) {
    text = newText;
    if (textBuffer) {
        vertex_buffer_clear(textBuffer);
        addText(textBuffer, newText);
    }
}

void pGraphics::pText::draw() {
    if (!showing)
        return;

    if (borderSize != 0)
        gfx->drawRectangle({ pos.first - borderSize, pos.second - borderSize }, { size.first + 2 * borderSize, size.second + 2 * borderSize }, borderColor);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, atlas->id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    mat4_set_identity(&gfx->model);
    mat4_translate(&gfx->model, pos.first, pos.second, 0);
    
    glUseProgram(textShader);
    glUniform1i(glGetUniformLocation(textShader, "texture" ), 0);
    glUniform3f(glGetUniformLocation(textShader, "pixel" ), 1.f / atlas->width, 1.f / atlas->height, atlas->depth);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "model" ), 1, 0, gfx->model.data);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "view" ), 1, 0, gfx->view.data);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "projection" ), 1, 0, gfx->projection.data);
    glUniformMatrix4fv(glGetUniformLocation(textShader, "projection" ), 1, 0, gfx->projection.data);
    vertex_buffer_render(textBuffer, GL_TRIANGLES);
    
    glDisable(GL_TEXTURE_2D);
    glUseProgram(0);
}

std::pair<float, float> pGraphics::pText::getTextSize(std::string pText) {
    if (pText.empty())
        return size;

    std::pair<float, float> textSize = { 0, texture_font_get_glyph(font, "H")->height };
    for (int i = 0; i < pText.size(); i++) {
        texture_glyph_t* glyph = texture_font_get_glyph(font, std::string({ pText.c_str()[i] }).c_str());
        if (glyph != NULL) {
            if (i > 0)
                textSize.first += texture_glyph_get_kerning(glyph, &pText.c_str()[i]);
            textSize.first += glyph->advance_x;
        }
    }
    return textSize;
}