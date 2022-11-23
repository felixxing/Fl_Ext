cmake_minimum_required(VERSION 3.20.0)
project(Fl_Ext VERSION 0.1.0)

# add_definitions(-DNO_BOX_EXT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)

file(GLOB_RECURSE SRC src/*.cpp)

# add files
add_executable(Fl_Ext main.cpp ${SRC})

include_directories(include)
include_directories(ext_include)
include_directories(FL)

target_link_libraries(Fl_Ext fltk)
target_link_libraries(Fl_Ext boost_filesystem-mt)
target_link_libraries(Fl_Ext ws2_32)
