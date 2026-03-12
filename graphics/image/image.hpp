#pragma once

#include "../../main.hpp"

class pGraphics::pImage : public pGraphics {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::string altText;
    std::string imageLocation;
    
    GLuint textureID = 0;
    bool loaded = false;

    public:
    pImage(std::pair<double, double> pPos, std::pair<double, double> pSize, std::string pAltText, std::string pImageLocation);
    ~pImage();
    
    void load();
    void draw(int alpha = 255);

    void setPos(std::pair<double, double> newPos);
    void setSize(std::pair<double, double> newSize);
    void setAltText(std::string newAltText);
    void setImage(std::string newImageLocation);
    std::string getImage();
    bool isImageLoaded();
};