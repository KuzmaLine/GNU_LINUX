#!/bin/sh

mkdir build
cd build; cmake ..
make
ctest
ctest -T Coverage
