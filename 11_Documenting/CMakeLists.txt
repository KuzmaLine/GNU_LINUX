cmake_minimum_required(VERSION 3.2)
project(find_num)

find_package(Gettext REQUIRED)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/po PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/find_num.po)

add_executable(find_num find_num.c)

install(TARGETS find_num DESTINATION ${CMAKE_INSTALL_PREFIX})
