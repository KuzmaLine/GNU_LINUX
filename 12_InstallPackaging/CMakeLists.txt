cmake_minimum_required(VERSION 3.9)
project("TESTS")

find_package(Gettext REQUIRED)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/po PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/tests.po)

set(GETTEXT_MO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/po)

install(DIRECTORY ${GETTEXT_MO_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/locale)

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

function(add_test_with_gettext name test_command command_param)
    add_executable(${name} tests.c)
    target_compile_definitions(${name} PRIVATE TEST_COMMAND=${test_command})

    set_target_properties(${name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    install(TARGETS ${name} DESTINATION ${CMAKE_INSTALL_PREFIX})

    add_test(NAME ${name} COMMAND ${name} ${command_param})
endfunction()

add_test_with_gettext(benchtest 0 558d2750ae0e0887)
add_test_with_gettext(capacity_test 1 0)  
add_test_with_gettext(size_init 2 0)
add_test_with_gettext(size_1 3 0)
add_test_with_gettext(value 4 0)
add_test_with_gettext(clear 5 0)
add_test_with_gettext(clear_not_free 6 0)
add_test_with_gettext(free 7 0)
add_test_with_gettext(clear_empty 8 0)
add_test_with_gettext(clear_no_op 9 0)
add_test_with_gettext(size_10000 10 0)
add_test_with_gettext(match_10000 11 0)
add_test_with_gettext(grow_1000 12 0)
add_test_with_gettext(size_0_grow 13 0)
add_test_with_gettext(trunc_100 14 0)
add_test_with_gettext(size_4 15 0)
add_test_with_gettext(size_3 17 0)
add_test_with_gettext(pop_3 16 0)
add_test_with_gettext(pop_2 18 0)
add_test_with_gettext(pop_1 19 0)
add_test_with_gettext(pop_0 20 0)
add_test_with_gettext(size_0_pop 21 0)

set_tests_properties(benchtest capacity_test size_init size_1 value clear 
                     clear_not_free free clear_empty clear_no_op size_10000 
                     match_10000 grow_1000 size_0_grow trunc_100 size_4 size_3 
                     pop_3 pop_2 pop_1 pop_0 size_0_pop
  PROPERTIES ENVIRONMENT "LANG=ru_RU.UTF-8;LC_ALL=ru_RU.UTF-8")
