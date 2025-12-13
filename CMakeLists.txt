cmake_minimum_required(VERSION 3.11)
project(laba)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main lib)

enable_testing()
add_subdirectory(tests)