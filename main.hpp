#pragma once

#ifdef _WIN32
    #define NDEBUG
    #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include <utility>
#include <strings.h>
#include <cmath>
#include <algorithm>
#include <random>

#include "include/IL/ilut.h"

#ifndef M_PI
    #define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
#endif

#include "include/GL/glut.h"

#define IL_USE_PRAGMA_LIBS
#define ILUT_USE_OPENGL
#undef interface

#include "structs.hpp"
#include "utils/utils.hpp"
#include "graphics/graphics.hpp"
#include "graphics/buton/buton.hpp"
#include "graphics/textBox/textBox.hpp"
#include "graphics/checkBox/checkBox.hpp"
#include "graphics/image/image.hpp"
#include "graphics/slider/slider.hpp"
#include "interface/interface.hpp"