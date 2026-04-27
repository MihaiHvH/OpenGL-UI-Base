#pragma once

class pGraphics {
    public:
        pGraphics();
        ~pGraphics();

        bool isInit = false;

        std::string windowName = "";
        std::pair<int, int> size = { 0, 0 };
        std::pair<int, int> minSize = { 0, 0 };
        std::pair<int, int> maxSize = { 0, 0 };
        
        GLFWwindow* window= nullptr;
        void(*renderFunction)();

        mat4 projection, view, model;

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
                colors::pColor borderColor;
                bool enabled = true;
                bool showing = true;

                void addBorder(float pBorderSize, colors::pColor pBorderColor) {
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

        std::unordered_map<std::string, std::unique_ptr<pButton>> buttons;
        std::unordered_map<std::string, std::unique_ptr<pImage>> images;
        std::unordered_map<std::string, std::unique_ptr<pSlider>> sliders;
        std::unordered_map<std::string, std::unique_ptr<pText>> texts;
        std::unordered_map<std::string, std::unique_ptr<pTextBox>> textBoxes;

        static void drawPolygon(std::vector<std::pair<float, float>> points, colors::pColor color);
        static void drawRectangle(std::pair<float, float> pos, std::pair<float, float> size, colors::pColor color);
        static void drawFilledCircle(std::pair<float, float> centrePos, float r, colors::pColor color);
        static void drawOutlinedCircle(std::pair<float, float> centrePos, float r, float lineThickness, colors::pColor color);
        static void drawFilledEllipse(std::pair<float, float> pos, std::pair<float, float> size, colors::pColor color);
        static void drawOutlinedEllipse(std::pair<float, float> pos, std::pair<float, float> size, float lineThickness, colors::pColor color);
        static void drawTriangle(std::pair<float, float> points[3], colors::pColor color);
        static bool mouseInRegion(std::pair<float, float> pos, std::pair<float, float> size);

        void processSpecialInput(int key, int scancode, int action, int mods);
        void processInput(unsigned int key);
        void handleMouseKeys(int button, int action, int mods);
        void handleMouseMovement(int x, int y);
        void handleMouseDrag(int x, int y);

        void onResize(int newWidth, int newHeight);
        void init();
};