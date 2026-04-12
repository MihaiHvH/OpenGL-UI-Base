#pragma once

#include "../../main.hpp"

class pGraphics::pImage : public pGraphics::pElement {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::string imageLocation;
    
    GLuint textureID = 0;
    bool loaded = false;

    pGraphics::pText* textObj = nullptr;

    public:
    pImage(pGraphics* gfx, std::pair<double, double> pos, std::pair<double, double> size, std::string imageLocation, std::string altText, std::string fontLocation);
    ~pImage();
    
    void load();
    void draw(int alpha = 255);

    void setPos(std::pair<double, double> newPos) { this->pos = newPos; };
    void setSize(std::pair<double, double> newSize) { this->size = newSize; };
    void setImage(std::string newImageLocation);
    
    std::pair<double, double> getPos() { return this->pos; };
    std::pair<double, double> getSize() { return this->size; };
    std::string getImage() { return imageLocation; };
    bool isImageLoaded() { return loaded; };
    pGraphics::pText* getTextObj() { return textObj; };
};