#pragma once

#include "../../main.hpp"

class pGraphics::pImage : public pGraphics {
    private:
    std::pair<double, double> pos;
    std::pair<double, double> size;
    std::string altText;
    std::string imageLocation;
    
    GLuint textureID;
    ILuint image;

    public:
    pImage(std::pair<double, double> pPos, std::pair<double, double> pSize, std::string pAltText, std::string pImageLocation);
    ~pImage();
    
    void load();
    void draw(int alpha = 255);
    void updatePos(std::pair<double, double> pPos);
    void updateSize(std::pair<double, double> pSize);
};