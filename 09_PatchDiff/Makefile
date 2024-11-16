GENERATES=*.out tmp.c

all: generate run

generate:
	cp lab.c tmp.c
	${CC} tmp.c -o lab0.out
	patch tmp.c < p1.patch
	${CC} tmp.c -o lab1.out
	patch tmp.c < p2.patch
	${CC} tmp.c -o lab2.out
	patch tmp.c < p3.patch
	${CC} tmp.c -o lab3.out

run: generate
	./lab0.out
	./lab1.out 4
	./lab2.out " @" 5
	./lab3.out 13 ".#" 6
	./lab3.out 10 ".#" 6

clean:
	rm -rf ${GENERATES}