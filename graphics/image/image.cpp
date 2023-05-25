#include "image.hpp"
#include <GL/gl.h>

pGraphics::pImage::~pImage() {

}

pGraphics::pImage::pImage(std::pair<int, int> pPos, std::pair<int, int> pSize, std::string pAltText, std::string pImageLocation) {
    pos = pPos;
    size = pSize;
    altText = pAltText;
    imageLocation = pImageLocation;
}

void pGraphics::pImage::load() {
    image = ilLoadImage(imageLocation.c_str());
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if (!image)
        printf("Failed to load image %s\n", imageLocation.c_str());
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
        glTexCoord2i(0, 0); glVertex3i(pos.first, pos.second, 0);
        glTexCoord2i(1, 0); glVertex3i(pos.first + size.first, pos.second, 0);
        glTexCoord2i(1, 1); glVertex3i(pos.first + size.first, pos.second + size.second, 0);
        glTexCoord2i(0, 1); glVertex3i(pos.first, pos.second + size.second, 0);
    }
    if (!image) {
        glColor4f(0.f, 0.f, 0.f, 1.f);
        glBegin(GL_POLYGON);
        glVertex2i(pos.first, pos.second); //corner down
        glVertex2i(pos.first + size.first, pos.second); //right down corner
        glVertex2i(pos.first + size.first, pos.second + size.second); //right up corner
        glVertex2i(pos.first, pos.second + size.second); //corner up

        glEnd();

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glColor4f(1.f, 0.f, 0.f, 1.f);
        const unsigned char* str = reinterpret_cast<const unsigned char*>(altText.c_str());
        std::pair<int, int> sz = { glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, altText[0]), glutBitmapLength(GLUT_BITMAP_HELVETICA_12, str) };
        glRasterPos2i(pos.first + size.first / 2 - sz.second / 2, pos.second + size.second / 2 + sz.first / 2);
        for (size_t i = 0; i < strlen(altText.c_str()); ++i)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, altText[i]);
    }
    glEnd();
}