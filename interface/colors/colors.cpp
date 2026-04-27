#include "../../main.hpp"

void colors::init() {
    createNewColor("black", 0, 0, 0);
    createNewColor("white", 255, 255,255);
    createNewColor("gray", 128, 128, 128);
    createNewColor("red", 255, 0, 0);
    createNewColor("green", 0, 255, 0);
    createNewColor("blue", 0, 0, 255);
    createNewColor("yellow", 255, 255, 0);
    createNewColor("cyan", 0, 255, 255);
    createNewColor("purple", 255, 0, 255);
    createNewColor("orange", 255, 165, 0);
    createNewColor("lime", 50, 205, 50);
    createNewColor("pink", 255, 192, 203);
    createNewColor("magenta", 255, 0, 255);
    createNewColor("gold", 255, 215, 0);
    createNewColor("deepSkyBlue", 0, 191, 255);
    createNewColor("maroon", 128, 0, 0);
    createNewColor("olive", 128, 128, 0);
    createNewColor("forestGreen", 34, 139, 34);
    createNewColor("navy", 0, 0, 128);
    createNewColor("brown", 165, 42, 42);
    createNewColor("sienna", 160, 82, 45);
    createNewColor("skyBlue", 135, 206, 235);
    createNewColor("mint", 189, 252, 201);
    createNewColor("lavender", 230, 230, 250);
    createNewColor("peach", 255, 218, 185);
    createNewColor("silver", 192, 192, 192);
    createNewColor("slateGray", 112, 128, 144);
    createNewColor("charcoal", 54, 69, 79);
    createNewColor("gunmetal", 44, 53, 57);
    createNewColor("midnight", 25, 25, 112);
}

void colors::createNewColor(std::string name, int r, int g, int b, int a) {
    if (color.find(name) != color.end())
        throw std::runtime_error("[createNewColor] Can't name two colors the same!");
    color[name] = pColor{ r, g, b, a };
}

void colors::modifyColor(std::string name, int r, int g, int b, int a) {
    if (color.find(name) == color.end()) {
        printf("[modifyColor] Color %s doesn't exist.\n", name);
        return;
    }
    color[name] = {r, g, b, a};
}

void colors::removeColor(std::string name) {
    if (color.find(name) == color.end())
        return;
    color.erase(name);
}