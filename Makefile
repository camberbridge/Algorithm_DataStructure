all: HomeWork1

HomeWork1: HomeWork1.c
	gcc -o $@ $^ #-lm
