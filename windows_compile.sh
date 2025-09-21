#!/bin/bash

files=`find . -name '*.*' -a \( -name '*.cpp' \)`

name=$1

if [ -z "$name" ]; then
    name="OpenGL-UI-Base"
fi

x86_64-w64-mingw32-g++ -I./include -L./lib $files -o $name -g -lopengl32 -lglu32 -lfreeglut -lDevIL
