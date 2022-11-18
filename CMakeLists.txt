cmake_minimum_required(VERSION 3.20.0)
project(Fl_Code VERSION 0.1.0)

#add_definitions(-DNO_BOX_EXT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)

file(GLOB_RECURSE SRC src/*.cpp)

# add files
add_executable(Fl_Code main.cpp ${SRC})

include_directories(include)
include_directories(FL)

target_link_libraries(Fl_Code ws2_32)
target_link_libraries(Fl_Code fltk)
target_link_libraries(Fl_Code boost_system-mt)
target_link_libraries(Fl_Code boost_filesystem-mt)
