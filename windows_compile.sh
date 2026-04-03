#!/bin/bash

name=$1
if [ -z "$name" ]; then
    name="OpenGL-UI-Base.exe"
fi

INCLUDES="-I./include"
FLAGS="-g -static -DGLEW_STATIC"
LIBS="-lglew32 -lglfw3 -lDevIL -lopengl32 -lfreetype -lgdi32"

C_FILES=$(find ./include/freetype-gl -maxdepth 1 -name "*.c")

CPP_FILES=$(find . -name "*.cpp")

C_OBJECTS=""
for src in $C_FILES; do
    obj="${src%.c}.o"
    x86_64-w64-mingw32-gcc -c "$src" -o "$obj" $INCLUDES $FLAGS
    C_OBJECTS="$C_OBJECTS $obj"
done

rm -f "$name"
x86_64-w64-mingw32-g++ $INCLUDES $FLAGS $CPP_FILES $C_OBJECTS -L./lib/windows -o "$name" $LIBS

echo "Built: $name"