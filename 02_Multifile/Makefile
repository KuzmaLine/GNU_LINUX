GENERATES = prog README liboutput_static.a liboutput.so prog-a prog-so test-no test-one test-three test-a-no test-a-one test-a-three test-so-no test-so-one test-so-three
TRASH = *.o o.* *~
CFLAGS = -Wall -fPIC

all: progs

.SECONDARY:	fun.o const.o
.INTERMEDIATE:	liboutput_static.a(fun.o const.o)

liboutput_static.a:	liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	${CC} $^ -o $@ -shared

prog: prog.o fun.o const.o
	${CC} $^ -o $@

prog-a: prog.o liboutput_static.a
	${CC} $^ -o $@

prog-so: prog.o liboutput.so
	${CC} $^ -o $@

progs:	prog prog-a prog-so

test: progs
	./prog > test-no 2>&1 && ./prog > test-one 2>&1 HERE  && ./prog > test-three 2>&1 abc cbd efg 
	./prog-a > test-a-no 2>&1 && ./prog-a > test-a-one 2>&1 HERE  && ./prog-a > test-a-three 2>&1 abc cbd efg 
	./prog-so > test-so-no 2>&1 && ./prog-so > test-so-one 2>&1 HERE  && ./prog-so > test-so-three 2>&1 abc cbd efg 
	cmp test-no test-a-no
	cmp test-so-no test-a-no 
	cmp test-one test-a-one
	cmp test-so-one test-a-one
	cmp test-three test-a-three
	cmp test-so-three test-a-three

fun.o prog.o:  outlib.h

clean:
	rm -f $(TRASH) $(GENERATES)