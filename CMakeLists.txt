cmake_minimum_required(VERSION 3.17)
project(HW7 C)


set(CMAKE_C_STANDARD 99)
include_directories(Include)
link_directories(libs)
add_executable(HW7 main.c grades.c)

target_link_libraries(HW7 liblinked-list.so)