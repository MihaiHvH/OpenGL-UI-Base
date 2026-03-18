#include "main.hpp"

pScreen screen;
pInterface interface;

pGraphics::pButton Button({ 10, 10}, { 100, 50 }, { interface.graphics.blue, interface.graphics.cyan }, GLUT_BITMAP_TIMES_ROMAN_24, interface.graphics.black, "Button", [](int state) {
    /*
        OnStateChange
    */
    printf("Button state: %d\n", state);
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

pGraphics::pText text({100, 100}, "include/freetype-gl/fonts/Vera.ttf", 20, "Hello World", interface.graphics.yellow);

void render() {
    glDisable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* RENDERING CODE */
    
    Button.draw();
    textBox.draw();
    checkBox.draw();
    slider.draw();
    image.draw();
    imageALT.draw();
    text.draw();

    glfwSwapBuffers(screen.window);
    glfwPollEvents();
}

void resize(GLFWwindow *window, int newWidth, int newHeight) {
    screen.size = { newWidth, newHeight };
    
    interface.graphics.onResize(newWidth, newHeight);
    
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, newWidth, newHeight, 0, -1, 1);
}

void processSpecialInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    textBox.onSpeciaKeyPress(key, action);
}

void processInput(GLFWwindow *window, unsigned int key) {
    textBox.onKeyPress(key);
}

void handleMouseKeys(GLFWwindow *window, int button, int action, int mods) {
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            screen.leftClick = action;
            
            if (screen.leftClick != GLFW_PRESS)
                break;

            Button.checkClick();
            textBox.checkClick();
            checkBox.checkClick();
            slider.handleMouse();

            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            screen.rightClick = action;

            if (screen.rightClick != GLFW_PRESS)
                break;

            break;
        }
    }
}

void handleMouseDrag(int x, int y) { 
    slider.handleMouse();
}

void handleMouseMovement(GLFWwindow *window, double x, double y) {
    screen.mousePointer = { x, y };
    if (screen.leftClick == GLFW_PRESS) handleMouseDrag(x, y);
}

void errorCallback(int error, const char* description) {
	printf("An error has occurred: %s", description);
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        printf("An error has occurred!");
        return 0;
    }

    GLFWwindow *window = glfwCreateWindow(screen.initialSize.first, screen.initialSize.second, screen.windowName.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screen.initialSize.first, screen.initialSize.second, 0, -1, 1);
    glClearColor(1, 1, 1, 1);
    
    screen.window = window;
    screen.render = render;

    glutInit(&argc, argv);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("Error: %s\n", glewGetErrorString(err) );
        return 0;
    }

    text.load();

    interface.graphics.init();

    /*image loading --start--*/

    ilInit();

    image.load();
    imageALT.load();

    glfwSetWindowSizeCallback(window, resize);
    glfwSetKeyCallback(window, processSpecialInput);
    glfwSetCharCallback(window, processInput);
    glfwSetMouseButtonCallback(window, handleMouseKeys);
    glfwSetCursorPosCallback(window, handleMouseMovement);

    while (!glfwWindowShouldClose(window))
        render();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}