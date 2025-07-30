#include "image.hpp"

pGraphics::pImage::~pImage() {

}

pGraphics::pImage::pImage(std::pair<double, double> pPos, std::pair<double, double> pSize, std::string pAltText, std::string pImageLocation) {
    pos = pPos;
    size = pSize;
    altText = pAltText;
    imageLocation = pImageLocation;
}

void pGraphics::pImage::load() {
    image = ilLoadImage(imageLocation.c_str());
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if (!image) {
        printf("Failed to load image %s\n", imageLocation.c_str());
    }
    else {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
        0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
        ilDeleteImage(image);
    }
}

void pGraphics::pImage::draw(int alpha) {
    if (image) {
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
        glDisable(GL_TEXTURE_2D);
        glEnd();
    }
    if (!image) {
        this->drawRect(pos, size, this->black);
        std::pair<int, int> sz = this->getTextSize(altText.c_str(), GLUT_BITMAP_HELVETICA_12);
        this->drawText({ pos.first + size.first / 2 - sz.first / 2, pos.second + size.second / 2 + sz.second / 2 }, GLUT_BITMAP_HELVETICA_12, altText.c_str(), this->red);
    }
}

void pGraphics::pImage::updatePos(std::pair<double, double> pPos) {
    pos = pPos;
}

void pGraphics::pImage::updateSize(std::pair<double, double> pSize) {
    size = pSize;
}