cmake_minimum_required(VERSION 3.13)

project(
    MyProject
    VERSION 1.0
    DESCRIPTION "CPP practice"
    LANGUAGES CXX)

# include_directories(include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} copy_constructor.cpp)

set(CMAKE_INSTALL_PREFIX /home/adw/workspace/cpp/241115_ch04-4)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)