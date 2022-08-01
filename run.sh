#!/bin/bash

MAIN="main"
OUTDIR="build"

if [ ! -d ./"$OUTDIR" ]; then
    mkdir "$OUTDIR"
fi

# debug mode
# gcc -o executable -std=c11 -Wall -ggdb3 main.c  # add -ggdb3 to it
gcc ./"$MAIN".c -o ./build/"$MAIN" -lm -lgd -lpng -lz -ljpeg -lfreetype && ./build/"$MAIN"
