CC = gcc	
LIBS = -lncursesw
CFLAGS = -Wall
SRC = Show.c
EXE = Show

all: $(SRC)
	$(CC) $(CFLAGS) $< $(LIBS) -o $(EXE)

clean:
	rm -f *.o $(EXE)