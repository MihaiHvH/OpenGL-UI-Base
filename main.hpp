#pragma once

#ifdef _WIN32
    #define IL_USE_PRAGMA_LIBS
    #define NDEBUG
    #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include <utility>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <random>

#include "include/IL/ilut.h"

#ifdef _WIN32
    #undef interface
#endif

#include "include/GL/glut.h"

#include "interface/interface.hpp"
#include "structs.hpp"
#include "graphics/graphics.hpp"
#include "graphics/buton/buton.hpp"
#include "graphics/textBox/textBox.hpp"
#include "graphics/checkBox/checkBox.hpp"
#include "graphics/image/image.hpp"
#include "graphics/slider/slider.hpp"
