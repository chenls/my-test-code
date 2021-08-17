if(CMAKE_TOOLCHAIN_FILE)
    set(LIBRARY_OUTPUT_PATH_ROOT ${CMAKE_BINARY_DIR} CACHE PATH "root for library output, set this to change where android libs are compiled to")
    # get absolute path, but get_filename_component ABSOLUTE only refer with source dir, so find_file here :(
    get_filename_component(CMAKE_TOOLCHAIN_FILE_NAME ${CMAKE_TOOLCHAIN_FILE} NAME)
    find_file(CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE_NAME} PATHS ${CMAKE_SOURCE_DIR} NO_DEFAULT_PATH)
    message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
endif()

cmake_minimum_required(VERSION 2.8.12)

project(test)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
# set(CMAKE_CXX_FLAGS "-g -static ${CMAKE_CXX_FLAGS}")

aux_source_directory(. DIR_SRCS)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--dynamic-linker=linker64 -Wl,-rpath=./")

add_executable(test ${DIR_SRCS} )
