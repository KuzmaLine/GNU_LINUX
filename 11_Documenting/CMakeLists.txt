cmake_minimum_required(VERSION 3.2)
project(find_num)

find_package(Gettext REQUIRED)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/po PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/find_num.po)

# Найти Doxygen
find_package(Doxygen)

# Если Doxygen найден, добавляем поддержку генерации документации
if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})  # Путь к исходникам
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)  # Путь для выходных файлов

    configure_file(Doxyfile.in Doxyfile @ONLY)  # Настроим Doxygen с помощью шаблона

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM)
endif()

add_executable(find_num find_num.c)

install(TARGETS find_num DESTINATION ${CMAKE_INSTALL_PREFIX})
