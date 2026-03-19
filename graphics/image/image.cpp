#include "image.hpp"

pGraphics::pImage::~pImage() {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

pGraphics::pImage::pImage(std::pair<double, double> pPos, std::pair<double, double> pSize, std::string pFontLocation, std::string pAltText, std::string pImageLocation) {
    pos = pPos;
    size = pSize;
    imageLocation = pImageLocation;

    textObj = new pGraphics::pText({ 0, 0 }, pFontLocation, 14, pAltText, this->red);
}

void pGraphics::pImage::load() {
    if (!loaded)
        textObj->load();

    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }

    loaded = false;
    
    ILuint image = ilLoadImage(imageLocation.c_str());
    if (!image) {
        printf("Failed to load image %s\n", imageLocation.c_str());
        return;
    }
    
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
    ilDeleteImage(image);
    loaded = true;
}

void pGraphics::pImage::draw(int alpha) {
    if (loaded && textureID != 0) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_QUADS);
        
        glColor4f(1.f, 1.f, 1.f, alpha / 255.f);
        glTexCoord2d(0, 0); glVertex3d(pos.first, pos.second, 0);
        glTexCoord2d(1, 0); glVertex3d(pos.first + size.first, pos.second, 0);
        glTexCoord2d(1, 1); glVertex3d(pos.first + size.first, pos.second + size.second, 0);
        glTexCoord2d(0, 1); glVertex3d(pos.first, pos.second + size.second, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else {
        this->drawRectangle(pos, size, this->black);
        std::pair<double, double> textSize = textObj->getTextSize();
        textObj->setPos({ pos.first + (size.first - textSize.first) / 2, pos.second + (size.second + textSize.second) / 2 });
        textObj->draw();
    }
}

void pGraphics::pImage::setImage(std::string newImageLocation) {
    imageLocation = newImageLocation;
    load();
}