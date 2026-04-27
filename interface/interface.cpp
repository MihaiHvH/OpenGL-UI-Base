#include "../main.hpp"

pInterface::pInterface() {
    colors::init();
}

pInterface::~pInterface() {

}

void pInterface::createNewWindow(std::string id, std::string name, int width, int height, void(*renderFunction)()) {
    if (window.find(id) != window.end() && window[id].isInit)
        throw std::runtime_error("[createNewWindow] You can't create two windows with the same id.");
    if (!sharedContextWindow) {
        sharedContextWindow = glfwCreateWindow(1, 1, "shared", NULL, NULL);
        glfwHideWindow(sharedContextWindow);
    }
    window[id].window = glfwCreateWindow(width, height, name.c_str(), NULL, sharedContextWindow);
    window[id].windowName = name;
    window[id].renderFunction = renderFunction;
    if (!window[id].window) {
        glfwTerminate();
        throw std::runtime_error("[createNewWindow] Error creating window.");
    }
    glfwMakeContextCurrent(window[id].window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window[id].size.first, window[id].size.second, 0, -1, 1);
    glClearColor(1, 1, 1, 1);

    if (glCreateProgram == nullptr) {
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK)
            throw std::runtime_error(reinterpret_cast<const char*>(glewGetErrorString(err)));
    }

    window[id].init();

    glfwSetWindowUserPointer(window[id].window, &window[id]);
    glfwSetWindowSizeCallback(window[id].window, [](GLFWwindow* window, int newWidth, int newHeight) {
        GLFWwindow* previousContext = glfwGetCurrentContext();
        glfwMakeContextCurrent(window);
        pGraphics* app = static_cast<pGraphics*>(glfwGetWindowUserPointer(window));
        if (app)
            app->onResize(newWidth, newHeight);
        glfwMakeContextCurrent(previousContext);
    });
    glfwSetKeyCallback(window[id].window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        pGraphics* app = static_cast<pGraphics*>(glfwGetWindowUserPointer(window));
        if (app)
            app->processSpecialInput(key, scancode, action, mods);
    });
    glfwSetCharCallback(window[id].window, [](GLFWwindow* window, unsigned int key) {
        pGraphics* app = static_cast<pGraphics*>(glfwGetWindowUserPointer(window));
        if (app)
            app->processInput(key);
    });
    glfwSetMouseButtonCallback(window[id].window, [](GLFWwindow* window, int button, int action, int mods) {
        pGraphics* app = static_cast<pGraphics*>(glfwGetWindowUserPointer(window));
        if (app)
            app->handleMouseKeys(button, action, mods);
    });
    glfwSetCursorPosCallback(window[id].window, [](GLFWwindow* window, double x, double y) {
        pGraphics* app = static_cast<pGraphics*>(glfwGetWindowUserPointer(window));
        if (app)
            app->handleMouseMovement(x, y);
    });
}

void pInterface::run() {
    while (true) {
        bool allClosed = true;
        for (auto it = window.begin(); it != window.end(); ) {
            pGraphics& data = it->second;
            if (!glfwWindowShouldClose(data.window)) {
                allClosed = false;
                glfwMakeContextCurrent(data.window);
                
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                data.renderFunction();

                glfwSwapBuffers(data.window);
                ++it;
            }
            else {
                glfwDestroyWindow(data.window);
                it = window.erase(it);
            }
        }
        if (allClosed) {
            if (sharedContextWindow) {
                glfwDestroyWindow(sharedContextWindow);
                sharedContextWindow = nullptr;
            }
            break;
        }
        glfwPollEvents();
    }
    glfwTerminate();
}

pGraphics::pButton* pInterface::createButton(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::vector<colors::pColor> colors, void(*function)(int)) {
    if (window[windowID].buttons.find(name) != window[windowID].buttons.end())
        throw std::runtime_error("[createButton] Error: You can't name two buttons the same!");
    window[windowID].buttons[name] = std::make_unique<pGraphics::pButton>(&window[windowID], pos, size, colors, function);
    return window[windowID].buttons.at(name).get();
}

pGraphics::pImage* pInterface::createImage(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::string imageLocation, std::string altText, std::string fontLocation) {
    if (window[windowID].images.find(name) != window[windowID].images.end())
        throw std::runtime_error("[createImage] Error: You can't name two images the same!");
    window[windowID].images[name] = std::make_unique<pGraphics::pImage>(&window[windowID], pos, size, imageLocation, altText, fontLocation);
    if (window[windowID].isInit)
        window[windowID].images[name]->load();
    return window[windowID].images.at(name).get();
}

pGraphics::pSlider* pInterface::createSlider(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, colors::pColor onColor, colors::pColor offColor, colors::pColor valueTextColor, void(*function)(float)) {
    if (window[windowID].sliders.find(name) != window[windowID].sliders.end())
        throw std::runtime_error("[createSlider] Error: You can't name two sliders the same!");
    window[windowID].sliders[name] = std::make_unique<pGraphics::pSlider>(&window[windowID], pos, size, minMax, decimals, fontLocation, valueTextSize, onColor, offColor, valueTextColor, function);
    if (window[windowID].isInit)
        window[windowID].sliders[name]->init();
    return window[windowID].sliders.at(name).get();
}

pGraphics::pText* pInterface::createText(std::string windowID, std::string name, std::pair<float, float> pos, std::string fontLocation, int fontSize, std::string text, colors::pColor textColor) {
    if (window[windowID].texts.find(name) != window[windowID].texts.end())
        throw std::runtime_error("[createText] Error: You can't name two texts the same!");
    window[windowID].texts[name] = std::make_unique<pGraphics::pText>(&window[windowID], pos, fontLocation, fontSize, text, textColor);
    if (window[windowID].isInit)
        window[windowID].texts[name]->load();
    return window[windowID].texts.at(name).get();
}

pGraphics::pTextBox* pInterface::createTextBox(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, int maxChr, std::string fontLocation, int fontSize, colors::pColor insideColor, colors::pColor barColor, colors::pColor textColor, void(*function)(std::string)) {
    if (window[windowID].textBoxes.find(name) != window[windowID].textBoxes.end())
        throw std::runtime_error("[createTextBox] Error: You can't name two textBoxes the same!");
    window[windowID].textBoxes[name] = std::make_unique<pGraphics::pTextBox>(&window[windowID], pos, size, maxChr, fontLocation, fontSize, insideColor, barColor, textColor, function);
    if (window[windowID].isInit)
        window[windowID].textBoxes[name]->init();
    return window[windowID].textBoxes.at(name).get();
}

void pInterface::removeButton(std::string windowID, std::string name) {
    window[windowID].buttons.erase(name);
}

void pInterface::removeImage(std::string windowID, std::string name) {
    window[windowID].images.erase(name);
}

void pInterface::removeSlider(std::string windowID, std::string name) {
    window[windowID].sliders.erase(name);
}

void pInterface::removeText(std::string windowID, std::string name) {
    window[windowID].texts.erase(name);
}

void pInterface::removeTextBox(std::string windowID, std::string name) {
    window[windowID].textBoxes.erase(name);
}