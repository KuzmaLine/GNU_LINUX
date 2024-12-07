GENERATES=po/ru build benchtest capacity_test clear clear_empty clear_no_op clear_not_free free grow_1000 match_10000 pop_0 pop_1 pop_2 pop_3 size_0_grow size_0_pop size_1 size_10000 size_3 size_4 size_init trunc_100 value

all: install

install_opt: install
	sudo mkdir -p /opt/buf_tests
	sudo cp buf.h /opt/buf_tests/.
	sudo cp tests.c /opt/buf_tests/.
	sudo cp -r po /opt/buf_tests/.
	sudo cp CMakeLists.txt /opt/buf_tests/.
	sudo cp Doxyfile.in /opt/buf_tests/.

delete:
	sudo rm -rf /opt/buf_tests

install:
	mkdir -p build
	cd build; cmake -DCMAKE_INSTALL_PREFIX=.. ..; make install; make doc;

test:
	cd build; ctest; ctest -T Coverage

doc:
	python3 -m http.server -d build/doc/html 5000

man:
	cd build; help2man -N ./benchtest > tests.1; man ./tests.1

clean:
	rm -rf ${GENERATES}
