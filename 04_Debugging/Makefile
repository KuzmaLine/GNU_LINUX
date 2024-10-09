GENERATES = range
CFLAGS = -Wall -fPIC
TRASH = *.o o.* *~

all: range

range: range.c
	${CC} -O0 -g $^ -o range


FILE := $(shell mktemp)
test: range
	gdb -x test_one.gdb --batch --quiet ./$< | grep @@@ > ${FILE}
	cmp ${FILE} test_one_correct.txt
	gdb -x test_two.gdb --batch --quiet ./$< | grep @@@ > ${FILE}
	cmp ${FILE} test_two_correct.txt
	rm -f ${FILE}
	@echo "TEST: OK"

clean:
	rm -f $(TRASH) $(GENERATES)