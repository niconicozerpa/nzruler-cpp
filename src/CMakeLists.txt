cmake_minimum_required(VERSION 3.1)
project (NZRuler)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
add_library(rulerclass nzruler.cxx)

add_executable(nzruler main.cxx)

target_link_libraries(nzruler Qt5::Widgets rulerclass)