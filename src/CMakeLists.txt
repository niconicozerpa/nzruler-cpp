cmake_minimum_required(VERSION 3.1)
project(NZRuler)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(Qt5Widgets REQUIRED)
include( "${wxWidgets_USE_FILE}" )

add_executable(nzruler main.cxx nzruler.cxx)

target_link_libraries(nzruler Qt5::Widgets ${wxWidgets_LIBRARIES})
