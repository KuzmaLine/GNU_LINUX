GENERATES=po/ru build

all: install

install:
	mkdir build
	cd build; cmake -DCMAKE_INSTALL_PREFIX=.. ..; make; make doc;

test:
	cd build; ctest; ctest -T Coverage

doc:
	python3 -m http.server -d build/doc/html 5000

man:
	cd build; help2man -N ./benchtest > tests.1; man ./tests.1

clean:
	rm -rf ${GENERATES}
