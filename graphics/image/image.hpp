#pragma once

#include "../../main.hpp"

class pGraphics::pImage : public pGraphics::pElement {
    private:
    std::pair<float, float> pos;
    std::pair<float, float> size;
    std::string imageLocation;
    
    GLuint textureID = 0;
    bool loaded = false;

    pGraphics::pText* textObj = nullptr;

    public:
    pImage(pGraphics* gfx, std::pair<float, float> pos, std::pair<float, float> size, std::string imageLocation, std::string altText, std::string fontLocation);
    ~pImage();
    
    void load();
    void draw(int alpha = 255);

    void setPos(std::pair<float, float> newPos) { this->pos = newPos; };
    void setSize(std::pair<float, float> newSize) { this->size = newSize; };
    void setImage(std::string newImageLocation);
    
    std::pair<float, float> getPos() { return this->pos; };
    std::pair<float, float> getSize() { return this->size; };
    std::string getImage() { return imageLocation; };
    bool isImageLoaded() { return loaded; };
    pGraphics::pText* getTextObj() { return textObj; };
};