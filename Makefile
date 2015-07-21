all: BQsort Msort test hoge BQMsort BQMsort_2

#HomeWork1: HomeWork1.c
#	gcc -o $@ $^ #-lm

BQsort: BQsort.c
	gcc -o $@ $^ 

#p: p.c
#	gcc -o $@ $^

Msort: Msort.c
	gcc -o $@ $^

test: test.c
	gcc -o $@ $^

hoge: hoge.c
	gcc -o $@ $^

BQMsort: BQMsort.c
	gcc -o $@ $^

BQMsort_2: BQMsort_2.c
	gcc -o $@ $^

