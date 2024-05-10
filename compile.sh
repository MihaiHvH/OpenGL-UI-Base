#!/bin/bash

files=`find . -name '*.*' -a \( -name '*.cpp' \)`

name=$1

if [ -z "$name" ]; then
    name="OpenGL-Base"
fi

g++ $files -o $name -g -lGL -lglut -lIL -lGLU