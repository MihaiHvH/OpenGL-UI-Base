#pragma once

#include "../../main.hpp"

class pGraphics::pImage : public pGraphics {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::string imageLocation;
    
    GLuint textureID = 0;
    bool loaded = false;

    pGraphics::pText* textObj;

    public:
    pImage(std::pair<double, double> pPos, std::pair<double, double> pSize, std::string pFontLocation, std::string pAltText, std::string pImageLocation);
    ~pImage();
    
    void load();
    void draw(int alpha = 255);

    void setPos(std::pair<double, double> newPos) { pos = newPos; };
    void setSize(std::pair<double, double> newSize) { size = newSize; };
    void setImage(std::string newImageLocation);
    
    std::pair<double, double> getPos() { return pos; };
    std::pair<double, double> getSize() { return size; };
    std::string getImage() { return imageLocation; };
    bool isImageLoaded() { return loaded; };
    pGraphics::pText* getTextObj() { return textObj; };
};