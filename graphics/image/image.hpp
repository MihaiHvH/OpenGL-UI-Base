#pragma once

#include "../../main.hpp"

class pGraphics::pImage {
    private:
    std::pair<int, int> pos;
    std::pair<int, int> size;
    std::string altText;
    std::string imageLocation;
    
    GLuint textureID;
    ILuint image;

    public:
    pImage(std::pair<int, int> pPos, std::pair<int, int> pSize, std::string pAltText, std::string pImageLocation);
    ~pImage();
    
    void load();
    void draw(int alpha = 255);
};