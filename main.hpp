#pragma once

#ifdef _WIN32
    #define NDEBUG
    #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#ifndef M_PI
    #define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067
#endif

#include <utility>
#include <strings.h>
#include <cmath>
#include <algorithm>
#include <random>

#include "include/GL/glew.h"
#include "include/GL/glut.h"
#include "include/GL/gl.h"
#include "include/IL/ilut.h"

#include "include/freetype-gl/texture-atlas.h"
#include "include/freetype-gl/vertex-buffer.h"
#include "include/freetype-gl/freetype-gl.h"

#undef interface
#define IL_USE_PRAGMA_LIBS
#define ILUT_USE_OPENGL

#include "structs.hpp"
#include "utils/utils.hpp"
#include "graphics/graphics.hpp"
#include "graphics/buton/buton.hpp"
#include "graphics/textBox/textBox.hpp"
#include "graphics/checkBox/checkBox.hpp"
#include "graphics/image/image.hpp"
#include "graphics/slider/slider.hpp"
#include "interface/interface.hpp"