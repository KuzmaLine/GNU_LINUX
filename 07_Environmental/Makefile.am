CFLAGS = -Wall -g
GENERATES = src/.dirstamp src/.deps src/*.o

bin_PROGRAMS=rhasher

rhasher_SOURCES=src/rhasher.c

clean:
	git clean -xdf
	rm -rf ${GENERATES}