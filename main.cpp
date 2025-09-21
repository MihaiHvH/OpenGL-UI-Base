#include "main.hpp"

pScreen screen;
pInterface interface;

pGraphics::pButon buton({ 10, 10}, { 100, 50 }, interface.graphics.blue, interface.graphics.cyan, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, "Button", [](bool state) {
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

pGraphics::pCheckBox checkBox({ 260, 10 }, { 30, 30 }, GLUT_BITMAP_TIMES_ROMAN_24, "Check #1", true, interface.graphics.black, interface.graphics.blue, interface.graphics.purple, interface.graphics.yellow, [](bool state) {
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

void render() {
    glDisable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* RENDERING CODE */

    buton.draw();
    textBox.draw();
    checkBox.draw();
    slider.draw();
    image.draw();
    imageALT.draw();

    glutSwapBuffers();
}

void resize(int newWidth, int newHeight) {
    screen.size = { newWidth, newHeight };
    
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( 0, newWidth, newHeight, 0);
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

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(screen.initialSize.first, screen.initialSize.second);
    glutCreateWindow (screen.windowName.c_str());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( 0, screen.initialSize.first, screen.initialSize.second, 0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    screen.render = render;

    /*image loading --start--*/

    ilInit();

    image.load();
    imageALT.load();

    /*image loading --end--*/

    glutDisplayFunc(render);
    glutKeyboardFunc(processInput);
    glutSpecialFunc(processSpecialInput);
    glutReshapeFunc(resize);
    glutMouseFunc(handleMouseKeys);
    glutPassiveMotionFunc(handleMouseMovement);
    glutMotionFunc(handleMouseDrag);
    glutIdleFunc(handleIdle); //Use only if needed, takes a lot of cpu
    glutMainLoop();

    return 0;
}