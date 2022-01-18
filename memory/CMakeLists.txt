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

set(CMAKE_C_FLAGS "-O0 -g -DANC_DEBUG -v")

# For [sanitizer_name] use one of the following:
# address for AddressSanitizer
# leak for LeakSanitizer
# thread for ThreadSanitizer
# undefined for UndefinedBehaviorSanitizer (other options are also available, see the UBSan section)
# memory for MemorySanitizer
# [Additional_flags] are other compilation flags, such as -fno-omit-frame-pointer, fsanitize-recover/fno-sanitize-recover, -fsanitize-blacklist, etc.
# Use [-g] to have file names and line numbers included in warning messages.
# Add optimization level [-OX] to get reasonable performance (see recommendations in the particular Sanitizer documentation).

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

if(CMAKE_TOOLCHAIN_FILE)
    # link_libraries("/home/chenliusheng/soft/android-ndk-r20/platforms/android-28/arch-arm/usr/lib/liblog.so")
    link_libraries("/home/chenliusheng/soft/android-ndk-r20/platforms/android-28/arch-arm64/usr/lib/liblog.so")
endif()

aux_source_directory(. DIR_SRCS)
add_executable(test ${DIR_SRCS})
