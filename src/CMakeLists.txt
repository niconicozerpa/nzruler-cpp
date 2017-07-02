cmake_minimum_required(VERSION 3.1)
project(NZRuler)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

add_library(rulerclass nzruler.cxx)
add_executable(nzruler main.cxx)

target_link_libraries(rulerclass Qt5::Widgets)
target_link_libraries(nzruler rulerclass Qt5::Widgets)
