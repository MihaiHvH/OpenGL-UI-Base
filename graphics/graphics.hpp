#pragma once

class pGraphics {
    public:
        pGraphics();
        ~pGraphics();

        class pText;
        class pButton;
        class pTextBox;
        class pImage;
        class pSlider;

        class pElement {
            public:
                pGraphics* gfx;

                std::pair<float, float> pos = { 0, 0 };
                std::pair<float, float> size = { 0, 0 };
                float borderSize = 0;
                pColor borderColor;
                bool enabled = true;
                bool showing = true;

                void addBorder(float pBorderSize, pColor pBorderColor) {
                    borderSize = pBorderSize;
                    borderColor = pBorderColor;
                }

                void removeBorder() {
                    borderSize = 0;
                }

                std::pair<float, float> getCenter() {
                    return { pos.first + size.first / 2.f, pos.second + size.second / 2.f };
                }

                virtual ~pElement() = default;
        };

        std::unordered_map<std::string, pButton*> buttons;
        std::unordered_map<std::string, pImage*> images;
        std::unordered_map<std::string, pSlider*> sliders;
        std::unordered_map<std::string, pText*> texts;
        std::unordered_map<std::string, pTextBox*> textBoxes;

        pButton* createButton(std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::vector<pColor> colors, void(*function)(int)); 
        pImage* createImage(std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::string imageLocation, std::string altText, std::string fontLocation);
        pSlider* createSlider(std::string name, std::pair<float, float> pos, std::pair<float, float> size, std::pair<float, float> minMax, int decimals, std::string fontLocation, int valueTextSize, pColor onColor, pColor offColor, pColor valueTextColor, void(*function)(float));
        pText* createText(std::string name, std::pair<float, float> pos, std::string fontLocation, int fontSize, std::string text, pColor textColor);
        pTextBox* createTextBox(std::string name, std::pair<float, float> pos, std::pair<float, float> size, int maxChr, std::string fontLocation, int fontSize, pColor insideColor, pColor barColor, pColor textColor, void(*function)(std::string));

        pColor white, black, gray, red, green, blue, yellow, cyan, purple;

        static void drawPolygon(std::vector<std::pair<float, float>> points, pColor color);
        static void drawRectangle(std::pair<float, float> pos, std::pair<float, float> size, pColor color);
        static void drawFilledCircle(std::pair<float, float> centrePos, float r, pColor color);
        static void drawOutlinedCircle(std::pair<float, float> centrePos, float r, float lineThickness, pColor color);
        static void drawFilledEllipse(std::pair<float, float> pos, std::pair<float, float> size, pColor color);
        static void drawOutlinedEllipse(std::pair<float, float> pos, std::pair<float, float> size, float lineThickness, pColor color);
        static void drawTriangle(std::pair<float, float> points[3], pColor color);
        static bool mouseInRegion(std::pair<float, float> pos, std::pair<float, float> size);

        static pColor createNewColor(int r, int g, int b, int a = 255);

        void processSpecialInput(GLFWwindow* window, int key, int scancode, int action, int mods);
        void processInput(GLFWwindow* window, unsigned int key);
        void handleMouseKeys(GLFWwindow* window, int button, int action, int mods);
        void handleMouseMovement(GLFWwindow* window, int x, int y);
        void handleMouseDrag(GLFWwindow* window, int x, int y);

        static void onResize(int newWidth, int newHeight);
        void init();
};