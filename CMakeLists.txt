cmake_minimum_required (VERSION 3.5)

project(cpp_log_lib)

add_definitions("-std=c++11 -Wall -g -pthread")

add_executable(main logging main.cpp logging.cpp)

set(CMAKE_THREAD_PREFER_PTHREAD On)
find_package(Threads REQUIRED)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS main DESTINATION bin)

include(CTest)
ENABLE_TESTING()
ADD_TEST(log_multi_test main logging main.cpp logging.cpp)