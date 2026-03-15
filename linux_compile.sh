#!/bin/bash

name=$1
if [ -z "$name" ]; then
    name="OpenGL-UI-Base"
fi

INCLUDES="-I./include"
FLAGS="-g"
LIBS="-lGL -lglut -lIL -lILU -lILUT -lGLEW -lfreetype -lpng -ljpeg -ltiff -lz -lbz2 -lglfw"

C_FILES=$(find ./include/freetype-gl -maxdepth 1 -name "*.c")

CPP_FILES=$(find . -name "*.cpp")

C_OBJECTS=""
for src in $C_FILES; do
    obj="${src%.c}.o"
    gcc -c "$src" -o "$obj" $INCLUDES $FLAGS
    C_OBJECTS="$C_OBJECTS $obj"
done

rm -f "$name"
g++ $INCLUDES $FLAGS $CPP_FILES $C_OBJECTS -L./lib/linux -o "$name" $LIBS
echo "Built: $name"