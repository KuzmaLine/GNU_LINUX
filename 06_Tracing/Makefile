GENERATES = move infile.txt infile_PROTECT.txt output.txt protect_remove.so
CFLAGS = -Wall
TRASH = *.o o.* *~

all: move protect_remove

move: move.c
	${CC} -O0 -g $^ -o move

protect_remove: protect_remove.c
	${CC} --shared -fPIC $^ -o protect_remove.so

test: move protect_remove
	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile.txt
	./move "infile.txt" "output.txt" || \
 	if [ ! $$? -eq 0 ] || [ -f infile.txt ] || [ ! -f output.txt ]; then \
		echo "COMMON TEST INCORRECT!"; \
		exit 1; \
	fi

	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile.txt
	strace -e openat -P infile.txt -e fault=openat:error=EACCES ./move "infile.txt" "output.txt" > /dev/null 2>&1 || \
	if [ ! "$$?" -eq 102 ] || [ ! -f infile.txt ] || [ -f output.txt ]; then \
		echo "OPEN TEST INCORRECT!"; \
		exit 1; \
	fi

	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile.txt
	strace -e close -P infile.txt -e fault=close:error=EPERM ./move "infile.txt" "output.txt" > /dev/null 2>&1 || \
	if [ ! $$? -eq 106 ] || [ ! -f infile.txt ] || [ -f output.txt ]; then \
		echo "CLOSE TEST INCORRECT!"; \
		exit 1; \
	fi
	
	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile.txt
	strace -e read -P infile.txt -e fault=read:error=EIO ./move "infile.txt" "output.txt" > /dev/null 2>&1 || \
	if [ ! $$? -eq 104 ] || [ ! -f infile.txt ] || [ -f output.txt ]; then \
		echo "READ TEST INCORRECT!"; \
		exit 1; \
	fi

	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile.txt
	strace -e write -P infile.txt -e fault=write:error=EIO ./move "infile.txt" "output.txt" > /dev/null 2>&1 || \
	if [ ! $$? -eq 105 ] || [ ! -f infile.txt ] || [ -f output.txt ]; then \
		echo "WRITE TEST INCORRECT!"; \
		exit 1; \
	fi

	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile.txt
	strace -e unlink -P infile.txt -e fault=unlink ./move "infile.txt" "output.txt" > /dev/null 2>&1 || \
	if [ ! $$? -eq 108 ] || [ ! -f infile.txt ] || [ -f output.txt ]; then \
		echo "UNLINK TEST INCORRECT!"; \
		exit 1; \
	fi

	echo "lkdgjdfsklgjr epogj;opcx;jvp eorwjfs;l djfew pofjxdlkvjdfsr" > infile_PROTECT.txt
	LD_PRELOAD=$(PWD)/protect_remove.so ./move "infile_PROTECT.txt" "output.txt" > /dev/null 2>&1 || \
	if [ ! $$? -eq 0 ] || [ ! -f infile_PROTECT.txt ] || [ ! -f output.txt ]; then \
		echo "LD_PRELOAD TEST INCORRECT!"; \
		exit 1; \
	fi

	@echo "TESTS: OK!"

clean:
	rm -f $(TRASH) $(GENERATES)