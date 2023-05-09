#pragma once

#include "../structs.hpp"
#include "../graphics/graphics.hpp"

class pInterface {
    private:

    public:
    pInterface();
    ~pInterface();

    pScreen screen;
    pGraphics graphics;
};