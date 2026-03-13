#!/bin/bash

name=$1
if [ -z "$name" ]; then
    name="OpenGL-UI-Base"
fi

INCLUDES="-I./include -I./include/freetype-gl"
FLAGS="-g"
LIBS="-lGL -lglut -lIL -lGLU -lGLEW -lfreetype"


C_FILES=$(find ./include/freetype-gl -maxdepth 1 -name "*.c")

CPP_FILES=$(find . -name "*.cpp")

C_OBJECTS=""
for src in $C_FILES; do
    obj="${src%.c}.o"
    x86_64-w64-mingw32-gcc -c "$src" -o "$obj" $INCLUDES $FLAGS
    C_OBJECTS="$C_OBJECTS $obj"
done

rm -f "$name"
x86_64-w64-mingw32-g++ $INCLUDES $FLAGS $CPP_FILES $C_OBJECTS -L./lib -o "$name" $LIBS

echo "Built: $name"