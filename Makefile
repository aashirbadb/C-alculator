test:
	make compile && make run

compile: expression.h main.c matrix.h equation.h utils.h
	mkdir -p build && gcc ./main.c -o ./build/main -lm

run:
	./build/main
