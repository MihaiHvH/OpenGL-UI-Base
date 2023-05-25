#pragma once

#ifdef _WIN32
	#define IL_USE_PRAGMA_LIBS
#endif

#include <utility>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

#include "include/IL/ilut.h"
#include "include/GL/glut.h"

#include "interface/interface.hpp"
#include "structs.hpp"
#include "graphics/graphics.hpp"
#include "graphics/buton/buton.hpp"
#include "graphics/textBox/textBox.hpp"
#include "graphics/checkBox/checkBox.hpp"
#include "graphics/image/image.hpp"
#include "graphics/slider/slider.hpp"