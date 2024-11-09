GENERATES=po/ru build find_num

all: install

install:
	mkdir build
	cd build; cmake -DCMAKE_INSTALL_PREFIX=.. ..; make install

clean:
	rm -rf ${GENERATES}