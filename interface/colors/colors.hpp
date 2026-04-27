#pragma once

namespace colors {
    struct pColor {
        int r, g, b, a;
    };
    void init();
    void createNewColor(std::string name, int r, int g, int b, int a = 255);
    void modifyColor(std::string name, int r, int g, int b, int a = 255);
    void removeColor(std::string name);
};

extern std::unordered_map<std::string, colors::pColor> color;