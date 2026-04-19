#pragma once

#include "../main.hpp"

class pInterface {
    public:
        pInterface();
        ~pInterface();

        std::unordered_map<std::string, pGraphics> window;
        GLFWwindow* sharedContextWindow = nullptr;

        void createNewWindow(std::string id, std::string name, int width, int height, void(*renderFunction)());
        void run();

        pGraphics::pButton* createButton(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::vector<colors::pColor> colors, void(*function)(int)); 
        pGraphics::pImage* createImage(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::string imageLocation, std::string altText, std::string fontLocation);
        pGraphics::pSlider* createSlider(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, colors::pColor onColor, colors::pColor offColor, colors::pColor valueTextColor, void(*function)(float));
        pGraphics::pText* createText(std::string windowID, std::string name, std::pair<float, float> pos, std::string fontLocation, int fontSize, std::string text, colors::pColor textColor);
        pGraphics::pTextBox* createTextBox(std::string windowID, std::string name, std::pair<float, float> pos, std::pair<float, float> size, int maxChr, std::string fontLocation, int fontSize, colors::pColor insideColor, colors::pColor barColor, colors::pColor textColor, void(*function)(std::string));

        void removeButton(std::string windowID, std::string name);
        void removeImage(std::string windowID, std::string name);
        void removeSlider(std::string windowID, std::string name);
        void removeText(std::string windowID, std::string name);
        void removeTextBox(std::string windowID, std::string name);
};