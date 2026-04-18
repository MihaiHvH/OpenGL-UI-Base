#include "main.hpp"

pScreen screen;
pInterface interface;

pGraphics::pButton* Button = interface.graphics.createButton("Example button", { 10, 10}, { 100, 50 }, { interface.graphics.blue, interface.graphics.cyan }, [](int state) {
    printf("Button state: %d\n", state);
});

pGraphics::pTextBox* textBox = interface.graphics.createTextBox("Example textBox", { 130, 10 }, { 100, 40 }, -1, "include/freetype-gl/fonts/Vera.ttf", 20, interface.graphics.gray, interface.graphics.purple, interface.graphics.black, [](std::string text) {
    printf("TextBox text: %s\n", text.c_str());
});

pGraphics::pButton* checkBox = interface.graphics.createButton("Example checkbox", { 260, 10 }, { 30, 30 }, { interface.graphics.purple, interface.graphics.yellow }, [](int state) {
    printf("CheckBox state: %d\n", state);
});

pGraphics::pImage* imageALT = interface.graphics.createImage("Example alt image", { 10, 200 }, { 100, 100 }, "include/freetype-gl/fonts/Vera.ttf", "ALT TEXT", "images/imagep.png");
pGraphics::pImage* image = interface.graphics.createImage("Example image", { 150, 200 }, { 100, 100 }, "include/freetype-gl/fonts/Vera.ttf", "ALT TEXT", "images/image.png");

pGraphics::pSlider* slider = interface.graphics.createSlider("Example slider", { 260, 50 }, { 120, 50 }, { 0.f, 100.f }, 2, "include/freetype-gl/fonts/Vera.ttf", 16, interface.graphics.blue, interface.graphics.yellow, interface.graphics.red, [](float value) {
    printf("Slider value: %f\n", value);
});

pGraphics::pText* text = interface.graphics.createText("Example text", { 260, 100 }, "include/freetype-gl/fonts/Vera.ttf", 20, "Hello World", interface.graphics.black);

void render() {
    glDisable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* RENDERING CODE */

    Button->draw();
    textBox->draw();
    checkBox->draw();
    slider->draw();
    image->draw();
    imageALT->draw();
    text->draw();

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
    interface.graphics.processSpecialInput(window, key, scancode, action, mods);
}

void processInput(GLFWwindow *window, unsigned int key) {
    interface.graphics.processInput(window, key);
}

void handleMouseKeys(GLFWwindow *window, int button, int action, int mods) {
    interface.graphics.handleMouseKeys(window, button, action, mods);
}

void handleMouseDrag(GLFWwindow* window, int x, int y) { 
    interface.graphics.handleMouseDrag(window, x, y);
}

void handleMouseMovement(GLFWwindow* window, double x, double y) {
    interface.graphics.handleMouseMovement(window, x, y);
}

void errorCallback(int error, const char* description) {
	printf("An error has occurred: %s.", description);
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        printf("An error has occurred!");
        return 0;
    }

    screen.window = glfwCreateWindow(screen.size.first, screen.size.second, screen.windowName.c_str(), NULL, NULL);

    if (!screen.window) {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(screen.window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screen.size.first, screen.size.second, 0, -1, 1);
    glClearColor(1, 1, 1, 1);
    
    screen.render = render;

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("Error: %s\n", glewGetErrorString(err) );
        return 0;
    }

    interface.graphics.init();

    glfwSetWindowSizeCallback(screen.window, resize);
    glfwSetKeyCallback(screen.window, processSpecialInput);
    glfwSetCharCallback(screen.window, processInput);
    glfwSetMouseButtonCallback(screen.window, handleMouseKeys);
    glfwSetCursorPosCallback(screen.window, handleMouseMovement);

    while (!glfwWindowShouldClose(screen.window))
        render();

    glfwDestroyWindow(screen.window);
    glfwTerminate();

    return 0;
}