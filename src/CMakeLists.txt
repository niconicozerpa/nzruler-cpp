cmake_minimum_required(VERSION 3.1)
project(NZRuler)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

if (MINGW)
    set(CMAKE_SHARED_LINKER_FLAGS "-mwindows")
endif ()

add_executable(nzruler main.cxx nzruler.cxx)

target_link_libraries(nzruler ${wxWidgets_LIBRARIES})
