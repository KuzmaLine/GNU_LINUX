cmake_minimum_required(VERSION 3.2)
project(find_num)

find_package(Gettext REQUIRED)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/po PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/find_num.po)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)

    configure_file(Doxyfile.in Doxyfile @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM)
endif()

add_executable(find_num find_num.c)

install(TARGETS find_num DESTINATION ${CMAKE_INSTALL_PREFIX})
