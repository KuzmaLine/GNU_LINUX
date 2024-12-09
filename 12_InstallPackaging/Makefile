GENERATES=po/ru build benchtest capacity_test clear clear_empty clear_no_op clear_not_free free grow_1000 match_10000 pop_0 pop_1 pop_2 pop_3 size_0_grow size_0_pop size_1 size_10000 size_3 size_4 size_init trunc_100 value share benchtest.1

all: install

install_root:
	echo "Устанавливается benchtest вместе с buf.h"
	sudo mkdir -p /opt/buf_tests
	sudo cp -r po /usr/bin/.
	sudo cp benchtest /usr/bin/.
	sudo cp buf.h /usr/include/buf.h
	help2man --locale ru_RU.UTF-8 -N ./benchtest > benchtest.1; sudo cp benchtest.1 /usr/share/man/ru/man1/benchtest.1.gz

delete:
	sudo rm -rf /opt/buf_tests
	sudo rm -f /usr/include/buf.h
	sudo rm -f /usr/bin/benchtest
	sudo rm -rf /usr/bin/po
	sudo rm -f /usr/share/man/ru/man1/benchtest.1.gz

install:
	mkdir -p build
	cd build; cmake -DCMAKE_INSTALL_PREFIX=.. ..; make install; make doc;
	cp build/bin/* .
	sudo cp -r po /usr/bin/.
	cd build; make -B install;

test:
	cd build; ctest; ctest -T Coverage

doc:
	python3 -m http.server -d build/doc/html 5000

man:
	cd build/bin; help2man -N ./benchtest > tests.1; man ./tests.1

clean:
	rm -rf ${GENERATES}
