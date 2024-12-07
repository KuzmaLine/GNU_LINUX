GENERATES=po/ru build find_num find_num.1

all: install

install:
	mkdir build
	cd build; cmake -DCMAKE_INSTALL_PREFIX=.. ..; make install; make doc

doc:
	python3 -m http.server -d build/docs/html 5000

man:
	help2man -N ./find_num > find_num.1
	man ./find_num.1

clean:
	rm -rf ${GENERATES}