#include "main.hpp"

pInterface interface;

void Render();

pGraphics::pButon buton({ 10, 10}, { 100, 50 }, interface.graphics.blue, interface.graphics.cyan, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, "Button", [](bool state) {
    /*
        OnClickFunction
    */
    printf("Buton state: %d\n", state);
});

pGraphics::pTextBox textBox({ 130, 10 }, { 100, 40 }, -1, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, interface.graphics.blue, interface.graphics.purple, interface.graphics.black, Render, [](std::string text) {
    /*
        OnEnterFunction
    */
    printf("TextBox text: %s\n", text.c_str());
});

pGraphics::pCheckBox checkBox({ 260, 10 }, { 30, 30 }, GLUT_BITMAP_TIMES_ROMAN_24, "Check #1", true, interface.graphics.black, interface.graphics.blue, interface.graphics.purple, interface.graphics.yellow, [](bool state) {
    /*
        OnStateChange
    */
    printf("CheckBox state: %d\n", state);
});

pGraphics::pImage image({ 10, 200 }, { 100, 100 }, "ALT TEXT", "images/imagep.png");

pGraphics::pSlider slider({ 260, 50 }, { 100, 50 }, { 0.f, 100.f }, 2, false, GLUT_BITMAP_TIMES_ROMAN_24, false, "Slider", interface.graphics.blue, interface.graphics.yellow, interface.graphics.black, interface.graphics.white, interface.graphics.red, Render, [](double value) {
    /*
        OnValueChange
    */
    printf("Slider value: %f\n", value);
});

void Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);

    /* RENDERING CODE */

    buton.draw(interface);
    textBox.draw(interface);
    checkBox.draw(interface);
    image.draw();
    slider.draw(interface);

    glutSwapBuffers();
}

void Resize(GLint newWidth, GLint newHeight) {
    if (newWidth >= 8 && newHeight >= 8) {
        glViewport( 0, 0, newWidth, newHeight );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0, GLdouble (newWidth), GLdouble (newHeight), 0, 0, 100);
        Render();
        glutPostRedisplay();
    }
}

void ProcessSpecialInput(int key, int x, int y) {
    switch (key) {

    }
    textBox.onSpeciaKeyPress(key);
}

void ProcessInput(unsigned char key, int x, int y) {
    switch (key) {
        
    }
    textBox.onKeyPress(key);
}

void HandleMouseKeys(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON: {
            interface.screen.leftClick = state;

            buton.checkClick(interface);
            textBox.checkClick(interface);
            checkBox.checkClick(interface);
            slider.handleMouse(interface);

            if (state != GLUT_DOWN)
                break;

            break;
        }
        case GLUT_RIGHT_BUTTON: {
            interface.screen.rightClick = state;

            if (state != GLUT_DOWN)
                break;

            break;
        }
    }
    Render();
}

void HandleMouseMovement(int x, int y) {
    interface.screen.mousePointer = { x, y };
}

void HandleMouseDrag(int x, int y) {
    interface.screen.mousePointer = { x, y };
    if (interface.screen.leftClick != interface.screen.leftClickDrag)
        interface.screen.leftClickDrag = interface.screen.leftClick;
    
    slider.handleMouse(interface);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(interface.screen.initialSize.first, interface.screen.initialSize.second);
    glutCreateWindow (interface.screen.windowName.c_str());

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, 640, 640, 0, 0, 100);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /*image loading --start--*/

    ilInit();

    image.load();

    /*image loading --end--*/

    glutDisplayFunc(Render);
    glutKeyboardFunc(ProcessInput);
    glutSpecialFunc(ProcessSpecialInput);
    glutReshapeFunc(Resize);
    glutMouseFunc(HandleMouseKeys);
    glutPassiveMotionFunc(HandleMouseMovement);
    glutMotionFunc(HandleMouseDrag);

    glutMainLoop();

    return 0;
}