 make: compile run

compile:
	clang++ main.cpp -o main.out -std=c++17 -O3
run:
	./main.out