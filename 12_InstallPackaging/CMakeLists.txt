cmake_minimum_required(VERSION 3.9)
project("TESTS")

find_package(Gettext REQUIRED)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/po PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/tests.po)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

    configure_file(Doxyfile.in Doxyfile @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM)
endif()

include(CTest)
enable_testing()

add_compile_options(-g -O0 --coverage)
add_link_options(--coverage)

add_executable(benchtest tests.c)
target_compile_definitions(benchtest PRIVATE TEST_COMMAND=0)
install(TARGETS benchtest DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(capacity_test tests.c )
target_compile_definitions(capacity_test PRIVATE TEST_COMMAND=1)
install(TARGETS capacity_test DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_init tests.c)
target_compile_definitions(size_init PRIVATE TEST_COMMAND=2)
install(TARGETS size_init DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_1 tests.c)
target_compile_definitions(size_1 PRIVATE TEST_COMMAND=3)
install(TARGETS size_1 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(value tests.c)
target_compile_definitions(value PRIVATE TEST_COMMAND=4)
install(TARGETS value DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(clear tests.c)
target_compile_definitions(clear PRIVATE TEST_COMMAND=5)
install(TARGETS clear DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(clear_not_free tests.c)
target_compile_definitions(clear_not_free PRIVATE TEST_COMMAND=6)
install(TARGETS clear_not_free DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(free tests.c)
target_compile_definitions(free PRIVATE TEST_COMMAND=7)
install(TARGETS free DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(clear_empty tests.c)
target_compile_definitions(clear_empty PRIVATE TEST_COMMAND=8)
install(TARGETS clear_empty DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(clear_no_op tests.c)
target_compile_definitions(clear_no_op PRIVATE TEST_COMMAND=9)
install(TARGETS clear_no_op DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_10000 tests.c)
target_compile_definitions(size_10000 PRIVATE TEST_COMMAND=10)
install(TARGETS size_10000 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(match_10000 tests.c)
target_compile_definitions(match_10000 PRIVATE TEST_COMMAND=11)
install(TARGETS match_10000 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(grow_1000 tests.c)
target_compile_definitions(grow_1000 PRIVATE TEST_COMMAND=12)
install(TARGETS grow_1000 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_0_grow tests.c)
target_compile_definitions(size_0_grow PRIVATE TEST_COMMAND=13)
install(TARGETS size_0_grow DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(trunc_100 tests.c)
target_compile_definitions(trunc_100 PRIVATE TEST_COMMAND=14)
install(TARGETS trunc_100 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_4 tests.c)
target_compile_definitions(size_4 PRIVATE TEST_COMMAND=15)
install(TARGETS size_4 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_3 tests.c)
target_compile_definitions(size_3 PRIVATE TEST_COMMAND=17)
install(TARGETS size_3 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(pop_3 tests.c)
target_compile_definitions(pop_3 PRIVATE TEST_COMMAND=16)
install(TARGETS pop_3 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(pop_2 tests.c)
target_compile_definitions(pop_2 PRIVATE TEST_COMMAND=18)
install(TARGETS pop_2 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(pop_1 tests.c)
target_compile_definitions(pop_1 PRIVATE TEST_COMMAND=19)
install(TARGETS pop_1 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(pop_0 tests.c)
target_compile_definitions(pop_0 PRIVATE TEST_COMMAND=20)
install(TARGETS pop_0 DESTINATION ${CMAKE_INSTALL_PREFIX})

add_executable(size_0_pop tests.c)
target_compile_definitions(size_0_pop PRIVATE TEST_COMMAND=21)
install(TARGETS size_0_pop DESTINATION ${CMAKE_INSTALL_PREFIX})

add_test(NAME CapacityInit
         COMMAND capacity_test)
add_test(NAME SizeInit
         COMMAND size_init)
add_test(NAME Size1
         COMMAND size_1)
add_test(NAME Value
         COMMAND value)
add_test(NAME Clear
         COMMAND clear)

add_test(NAME ClearNotFree
         COMMAND clear_not_free)
add_test(NAME Free
         COMMAND free)
add_test(NAME ClearEmpty
         COMMAND clear_empty)
add_test(NAME ClearNoOp
         COMMAND clear_no_op)
add_test(NAME Size10000
         COMMAND size_10000)
add_test(NAME Match10000
         COMMAND match_10000)
add_test(NAME Grow1000
         COMMAND grow_1000)
add_test(NAME Size0Grow
         COMMAND size_0_grow)
add_test(NAME Trunc100
         COMMAND trunc_100)
add_test(NAME Size4
         COMMAND size_4)
add_test(NAME Size3
         COMMAND size_3)
add_test(NAME Pop3
         COMMAND pop_3)
add_test(NAME Pop2
         COMMAND pop_2)
add_test(NAME Pop1
         COMMAND pop_1)
add_test(NAME Pop0
         COMMAND pop_0)
add_test(NAME Size0Pop
         COMMAND size_0_pop)
add_test(NAME benchtest
         COMMAND benchtest 558d2750ae0e0887)
