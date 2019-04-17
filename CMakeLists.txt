cmake_minimum_required(VERSION 3.13)
project(copydestructor)

set(CMAKE_CXX_STANDARD 14)

# SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(copydestructor main.cpp)

#target_link_libraries (copydestructor ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(copydestructor Threads::Threads)