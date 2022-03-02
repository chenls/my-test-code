cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

add_executable(main main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(main PUBLIC Threads::Threads)
