#include "main.hpp"

pScreen screen;
pInterface interface;

pGraphics::pButon buton({ 10, 10}, { 100, 50 }, { interface.graphics.blue, interface.graphics.cyan }, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, "Button", [](int state) {
    /*
        OnClickFunction
    */
    printf("Buton state: %d\n", state);
});

pGraphics::pTextBox textBox({ 130, 10 }, { 100, 40 }, -1, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, interface.graphics.blue, interface.graphics.purple, interface.graphics.black, [](std::string text) {
    /*
        OnEnterFunction
    */
    printf("TextBox text: %s\n", text.c_str());
});

pGraphics::pCheckBox checkBox({ 260, 10 }, { 30, 30 }, GLUT_BITMAP_TIMES_ROMAN_24, "Check #1", true, interface.graphics.black, interface.graphics.blue, { interface.graphics.purple, interface.graphics.yellow }, [](int state) {
    /*
        OnStateChange
    */
    printf("CheckBox state: %d\n", state);
});

pGraphics::pImage imageALT({ 10, 200 }, { 100, 100 }, "ALT TEXT", "images/imagep.png");
pGraphics::pImage image({ 150, 200 }, { 100, 100 }, "ALT TEXT", "images/image.png");

pGraphics::pSlider slider({ 260, 50 }, { 100, 50 }, { 0.f, 100.f }, -1, false, GLUT_BITMAP_TIMES_ROMAN_24, false, "Slider", interface.graphics.blue, interface.graphics.yellow, interface.graphics.black, interface.graphics.white, interface.graphics.red, [](double value) {
    /*
        OnValueChange
    */
    printf("Slider value: %f\n", value);
});

#include "include/freetype-gl/mat4.h"
#include "include/freetype-gl/shader.h"

GLuint shader;
texture_atlas_t *atlas;
vertex_buffer_t *buffer;
mat4   model, view, projection;

typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex_t;

#include <cstring>

void add_text( vertex_buffer_t * buffer, texture_font_t * font,
               char * text, vec4 * color, vec2 * pen )
{
    size_t i;
    float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for( i = 0; i < strlen(text); ++i )
    {
        texture_glyph_t *glyph = texture_font_get_glyph( font, text + i );
        if( glyph != NULL )
        {
            float kerning =  0.0f;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text + i - 1 );
            }
            pen->x += kerning;
            int x0  = (int)( pen->x + glyph->offset_x );
            int y0  = (int)( pen->y + glyph->offset_y );
            int x1  = (int)( x0 + glyph->width );
            int y1  = (int)( y0 - glyph->height );
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;
            GLuint indices[6] = {0,1,2, 0,2,3};
            vertex_t vertices[4] = { { x0,y0,0,  s0,t0,  r,g,b,a },
                                     { x0,y1,0,  s0,t1,  r,g,b,a },
                                     { x1,y1,0,  s1,t1,  r,g,b,a },
                                     { x1,y0,0,  s1,t0,  r,g,b,a } };
            vertex_buffer_push_back( buffer, vertices, 4, indices, 6 );
            pen->x += glyph->advance_x;
        }
    }
}

void render() {
    glDisable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(0);
    
    /* RENDERING CODE */
    
    buton.draw();
    textBox.draw();
    checkBox.draw();
    slider.draw();
    image.draw();
    imageALT.draw();
    

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glUseProgram( shader );
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, atlas->id);
        glUniform1i( glGetUniformLocation( shader, "texture" ),
                     0 );
        glUniformMatrix4fv( glGetUniformLocation( shader, "model" ),
                            1, 0, model.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "view" ),
                            1, 0, view.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "projection" ),
                            1, 0, projection.data);
        vertex_buffer_render( buffer, GL_TRIANGLES );
    }
    glEnd();

    glutSwapBuffers();
}

void resize(int newWidth, int newHeight) {
    screen.size = { newWidth, newHeight };
    
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, newWidth, newHeight, 0);

    mat4_set_orthographic(&projection, 0, newWidth, 0, newHeight, -1, 1);

    glutPostRedisplay();
}

void processSpecialInput(int key, int x, int y) {
    textBox.onSpeciaKeyPress(key);
}

void processInput(unsigned char key, int x, int y) {
    textBox.onKeyPress(key);
}

void handleMouseKeys(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON: {
            screen.leftClick = state;

            if (state != GLUT_DOWN)
                break;

            buton.checkClick();
            textBox.checkClick();
            checkBox.checkClick();
            slider.handleMouse();

            break;
        }
        case GLUT_RIGHT_BUTTON: {
            screen.rightClick = state;

            if (state != GLUT_DOWN)
                break;

            break;
        }
    }
}

void handleMouseMovement(int x, int y) {
    screen.mousePointer = { x, y };
}

void handleMouseDrag(int x, int y) {
    screen.mousePointer = { x, y };
    if (screen.leftClick != screen.leftClickDrag)
        screen.leftClickDrag = screen.leftClick;
    
    slider.handleMouse();
}

void handleIdle() {

}

void init( void )
{
    size_t i;
    texture_font_t *font = 0;
    atlas = texture_atlas_new( 512, 512, 1 );
    const char * filename = "include/freetype-gl/fonts/Vera.ttf";
    char * text = "A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
    buffer = vertex_buffer_new( "vertex:3f,tex_coord:2f,color:4f" );
    vec2 pen = {{5, 400}};
    vec4 black = {{0,0,0,1}};
    for( i = 7; i < 27; ++i )
    {
        font = texture_font_new_from_file( atlas, i, filename );
        pen.x = 5;
        pen.y -= font->height;
        texture_font_load_glyphs( font, text );
        add_text( buffer, font, text, &black, &pen );
        texture_font_delete( font );
    }

    glGenTextures( 1, &atlas->id );
    glBindTexture( GL_TEXTURE_2D, atlas->id );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, atlas->width, atlas->height,
                  0, GL_RED, GL_UNSIGNED_BYTE, atlas->data );

    shader = shader_load("include/freetype-gl/shaders/v3f-t2f-c4f.vert",
                         "include/freetype-gl/shaders/v3f-t2f-c4f.frag");

    // THIS is the fix — set actual orthographic projection
    mat4_set_orthographic( &projection, 0, screen.initialSize.first,
                           0, screen.initialSize.second, -1, 1 );
    mat4_set_identity( &model );
    mat4_set_identity( &view );
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(screen.initialSize.first, screen.initialSize.second);
    glutCreateWindow (screen.windowName.c_str());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, screen.initialSize.first, screen.initialSize.second, 0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    screen.render = render;

    /*image loading --start--*/

    ilInit();

    image.load();
    imageALT.load();

    /*font loading*/

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
        exit( EXIT_FAILURE );
    }
    fprintf( stderr, "Using GLEW %s\n", glewGetString(GLEW_VERSION) );
#endif

    init();

    glutDisplayFunc(render);
    glutKeyboardFunc(processInput);
    glutSpecialFunc(processSpecialInput);
    glutReshapeFunc(resize);
    glutMouseFunc(handleMouseKeys);
    glutPassiveMotionFunc(handleMouseMovement);
    glutMotionFunc(handleMouseDrag);
    glutIdleFunc(handleIdle); //Use only if needed, takes a lot of cpu
    glutMainLoop();

    glDeleteTextures( 1, &atlas->id );
    atlas->id = 0;
    texture_atlas_delete( atlas );

    return 0;
}