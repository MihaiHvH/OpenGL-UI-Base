#include "main.hpp"

pScreen screen;
std::unordered_map<std::string, colors::pColor> color;
pInterface interface;

pGraphics::pButton* Button = interface.createButton("Main Window", "Example button", { 10, 10}, { 100, 50 }, { color["blue"], color["cyan"] }, [](int state) {
    printf("Button state: %d\n", state);
});

pGraphics::pTextBox* textBox = interface.createTextBox("Main Window", "Example textBox", { 130, 10 }, { 100, 40 }, -1, "fonts/Vera.ttf", 20, color["gray"], color["purple"], color["black"], [](std::string text) {
    printf("TextBox text: %s\n", text.c_str());
});

pGraphics::pButton* checkBox = interface.createButton("Main Window", "Example checkbox", { 260, 10 }, { 30, 30 }, { color["purple"], color["yellow"] }, [](int state) {
    printf("CheckBox state: %d\n", state);
});

pGraphics::pImage* imageALT = interface.createImage("Main Window", "Example alt image", { 10, 200 }, { 100, 100 }, "fonts/Vera.ttf", "ALT TEXT", "images/imagep.png");
pGraphics::pImage* image = interface.createImage("Main Window", "Example image", { 150, 200 }, { 100, 100 }, "fonts/Vera.ttf", "ALT TEXT", "images/image.png");

pGraphics::pSlider* slider = interface.createSlider("Main Window", "Example slider", { 260, 50 }, { 120, 50 }, { 0.f, 100.f }, 2, "fonts/Vera.ttf", 16, color["blue"], color["yellow"], color["red"], [](float value) {
    printf("Slider value: %f\n", value);
});

pGraphics::pText* text = interface.createText("Main Window", "Example text", { 10, 100 }, "fonts/Vera.ttf", 20, "Hello World", color["black"]);

pGraphics::pText* textPop = interface.createText("Secondary window", "Pop-up text", { 10, 10 }, "fonts/Vera.ttf", 20, "Notification", color["red"]);

void render() {
    /* RENDERING CODE */

    Button->draw();
    textBox->draw();
    checkBox->draw();
    slider->draw();
    image->draw();
    imageALT->draw();
    text->draw();
}

void errorCallback(int error, const char* description) {
	printf("An error has occurred: %s.", description);
}

int main(int argc, char** argv) {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        printf("An error has occurred!");
        return 0;
    }

    interface.createNewWindow("Main Window", "OpenGL-UI-Base", 640, 640, render);
    interface.setWindowSizeLimits("Main Window", { 120, 120 }, { 640, 640 });
    interface.createNewWindow("Secondary window", "Pop-up", 120, 120, []() {
        // render lambda function
        textPop->setPos({ interface.window["Secondary window"].size.first / 2 - textPop->getTextSize().first / 2, interface.window["Secondary window"].size.second / 2 - textPop->getTextSize().second / 2 });
        textPop->draw();
    });
    // border example
    Button->addBorder(3, color["gunmetal"]);
    checkBox->addBorder(5, color["black"]);
    //

    interface.run();

    return 0;
}