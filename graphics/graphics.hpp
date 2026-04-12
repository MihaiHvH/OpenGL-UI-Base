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

                std::pair<double, double> pos = { 0, 0 };
                std::pair<double, double> size = { 0, 0 };
                double borderSize = 0;
                pColor borderColor;

                void addBorder(double pBorderSize, pColor pBorderColor) {
                    borderSize = pBorderSize;
                    borderColor = pBorderColor;
                }

                void removeBorder() {
                    borderSize = 0;
                }

                virtual ~pElement() = default;
        };

        pButton* createButton(std::pair<double, double> pos, std::pair<double, double> size, std::vector<pColor> colors, void(*function)(int)); 
        pImage* createImage(std::pair<double, double> pos, std::pair<double, double> size, std::string imageLocation, std::string altText, std::string fontLocation);
        pSlider* createSlider(std::pair<double, double> pos, std::pair<double, double> size, std::pair<double, double> minMax, int decimals, std::string fontLocation, int valueTextSize, pColor onColor, pColor offColor, pColor valueTextColor, void(*function)(double));
        pText* createText(std::pair<double, double> pos, std::string fontLocation, int fontSize, std::string text, pColor textColor);
        pTextBox* createTextBox(std::pair<double, double> pos, std::pair<double, double> size, int maxChr, std::string fontLocation, int fontSize, pColor insideColor, pColor barColor, pColor textColor, void(*function)(std::string));

        pColor white, black, gray, red, green, blue, yellow, cyan, purple;

        void drawPolygon(std::vector<std::pair<double, double>> points, pColor color);
        void drawRectangle(std::pair<double, double> pos, std::pair<double, double> size, pColor color);
        void drawFilledCircle(std::pair<double, double> centrePos, double r, pColor color);
        void drawOutlinedCircle(std::pair<double, double> centrePos, double r, double lineThickness, pColor color);
        void drawFilledEllipse(std::pair<double, double> pos, std::pair<double, double> size, pColor color);
        void drawOutlinedEllipse(std::pair<double, double> pos, std::pair<double, double> size, double lineThickness, pColor color);
        void drawTriangle(std::pair<double, double> points[3], pColor color);
        bool mouseInRegion(std::pair<double, double> pos, std::pair<double, double> size);

        pColor createNewColor(int r, int g, int b, int a = 255);

        void onResize(int newWidth, int newHeight);
        void init();
};