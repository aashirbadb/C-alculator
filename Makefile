CC = gcc
CFLAGS = -lm -lgd -lpng -lz -ljpeg -lfreetype

test: 
	make compile && make run

compile: expression.h main.c matrix.h quadratic.h ui.h utils.h
	gcc ./main.c -o ./build/main -lm 
	
run: 
	./build/main