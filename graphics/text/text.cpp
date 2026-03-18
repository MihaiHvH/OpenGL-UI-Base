#include "text.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include <freetype-gl/shader.h>
#include <freetype-gl/vertex-buffer.h>
#include <freetype-gl/texture-font.h>
#include <freetype-gl/texture-atlas.h>
#include <freetype-gl/mat4.h>

static std::unordered_map<std::string, texture_font_t*> fontCache;
static texture_atlas_t* atlas = nullptr;

void pGraphics::pText::add_text( vertex_buffer_t * buffer, texture_font_t * font,
               char * text, vec4 * color, vec2 * pen )
{
    size_t i;
    float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for( i = 0; i < strlen(text); ++i )
    {
        texture_glyph_t *glyph = texture_font_get_glyph( font, text + i );
        if( glyph != NULL )
        {
            float kerning = 0.0f;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text + i - 1 );
            }
            pen->x += kerning;
            int x0  = (int)( pen->x + glyph->offset_x );
            int y0  = (int)( pen->y - glyph->offset_y );
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
            vertex_buffer_push_back_indices( buffer, indices, 6 );
            vertex_buffer_push_back_vertices( buffer, vertices, 4 );
            pen->x += glyph->advance_x;
        }
    }
}

void pGraphics::pText::init(int width, int height) {
    size_t i;
    texture_font_t *font = 0;
    atlas = texture_atlas_new( 512, 512, 3 );
    const char * filename = "include/freetype-gl/fonts/Vera.ttf";
    char * text = "A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
    text_buffer = vertex_buffer_new( "vertex:3f,tex_coord:2f,color:4f,ashift:1f,agamma:1f" );
    vec2 pen = {{0,0}};
    vec4 color = {{0,0,0,1}};

    for( i=7; i < 27; ++i)
    {
        font = texture_font_new_from_file( atlas, i, filename );
        pen.x = 0;
        pen.y -= font->height;
        texture_font_load_glyphs( font, text );
        add_text( text_buffer, font, text, &color, &pen );
        texture_font_delete( font );
    }

    glGenTextures( 1, &atlas->id );
    glBindTexture( GL_TEXTURE_2D, atlas->id );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, atlas->width, atlas->height,
                  0, GL_RGB, GL_UNSIGNED_BYTE, atlas->data );

    text_shader = shader_load( "include/freetype-gl/shaders/text.vert",
                          "include/freetype-gl/shaders/text.frag" );
    
    mat4_set_identity( &projection );
    mat4_set_identity( &model );
    mat4_set_identity( &view );
    onResize(width, height);
}

void pGraphics::pText::cleanup() {
    glDeleteTextures( 1, &atlas->id );
    atlas->id = 0;
    texture_atlas_delete( atlas );
}

void pGraphics::pText::onResize(int width, int height) {
    mat4_set_orthographic(&projection, 0, width, height, 0, -1, 1);
}

pGraphics::pText::pText(std::pair<double, double> pPos, std::string pFontLocation, std::string pText, pColor pTextColor) {
    pos = pPos;
    fontLocation = pFontLocation;
    text = pText;
    color = pTextColor;
}

pGraphics::pText::~pText() {}

void pGraphics::pText::draw() {
    int viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );

    glEnable( GL_TEXTURE_2D );

    glBindTexture(GL_TEXTURE_2D, atlas->id);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glColor4f( 0, 0, 0, 1 );
    glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );

    mat4_set_identity( &model );
    mat4_translate( &model, pos.first, pos.second, 0);
    glUseProgram( text_shader );
    {
        glUniform1i( glGetUniformLocation( text_shader, "texture" ),
                     0 );
        glUniform3f(  glGetUniformLocation( text_shader, "pixel" ),
                      1.0/atlas->width, 1.0/atlas->height, atlas->depth );
        glUniformMatrix4fv( glGetUniformLocation( text_shader, "model" ),
                            1, 0, model.data);
        glUniformMatrix4fv( glGetUniformLocation( text_shader, "view" ),
                            1, 0, view.data);
        glUniformMatrix4fv( glGetUniformLocation( text_shader, "projection" ),
                            1, 0, projection.data);
        glUniformMatrix4fv( glGetUniformLocation( text_shader, "projection" ),
                            1, 0, projection.data);
        vertex_buffer_render( text_buffer, GL_TRIANGLES );
    }
    glDisable(GL_TEXTURE_2D);
    glUseProgram(0);
}