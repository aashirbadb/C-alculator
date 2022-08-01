#pragma once

#include <gd.h>
#include<stdio.h>

void makeGraph(){
    gdImagePtr image;
    FILE *pngOut;
    
    int black,white;
    image = gdImageCreate(64,64);

    gdImageDestroy(image);
}
