GENERATES = esub res.txt res_correct.txt
CFLAGS = -Wall
TRASH = *.o o.* *~

all: esub

esub: esubc.c
	${CC} -O0 -g $^ -o esub

FILE := $(shell mktemp)

test: esub
	echo 'abcd abcd' | sed -E 's/ab(.*?)ab/\1/' > res_correct.txt
	./esub 'ab(.*?)ab' '\1' 'abcd abcd' > res.txt
	cmp res_correct.txt res.txt

	echo "abbbb cdef" | sed -E 's/(a)(b*?)/\2\1/' > res_correct.txt
	./esub '(a)(b*?)' '\2\1' 'abbbb cdef' > res.txt
	cmp res_correct.txt res.txt

	echo "abbbb cdef" | sed -E 's/(a)(b*?)/\\2\1/' > res_correct.txt
	./esub '(a)(b*?)' '\\2\1' 'abbbb cdef' > res.txt
	cmp res_correct.txt res.txt

	echo "abbbb cdef" | sed -E 's/(a)(b*?)/\\\2\1/' > res_correct.txt
	./esub '(a)(b*?)' '\\\2\1' 'abbbb cdef' > res.txt
	cmp res_correct.txt res.txt

	@echo "TEST: OK"

clean:
	rm -f $(TRASH) $(GENERATES)