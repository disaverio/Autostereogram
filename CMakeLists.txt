cmake_minimum_required(VERSION 3.6)
project(Autostereogram)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES autostereogram.c autostereogram.h color_utils.c color_utils.h drawing_utils.c drawing_utils.h)
add_executable(autostereogram ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(autostereogram ${GTK3_LIBRARIES})