# Installation and Running
## 1. Download and Install libgd.
 ```
    git clone https://github.com/libgd/libgd.git
    cd libgd
    make install
 ```
## 2. Compile and Running
```
    gcc main.c -o ./build/main -lm -lgd -lpng -lz -ljpeg -lfreetype
    ./build/main
```
