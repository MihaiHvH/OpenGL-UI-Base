#!/bin/bash

replacement="$1"

if [ -z "$replacement" ]; then
    replacement="OpenGL-UI-Base"
fi

find . -type f -name "*OpenGL-UI-Base*" | while read -r file; do
    dir=$(dirname "$file")
    base=$(basename "$file")
    newbase="${base//OpenGL-UI-Base/$replacement}"
    if [ "$base" != "$newbase" ]; then
        mv -v "$file" "$dir/$newbase"
    fi
done

find . -type f ! -path "./.git/*" -exec grep -Il "" {} + | while read -r file; do
    if grep -q "OpenGL-UI-Base" "$file"; then
        echo "Updating: $file"
        sed -i "s/OpenGL-UI-Base/$replacement/g" "$file"
    fi
done
