cmake_minimum_required(VERSION 3.26)

project(HomeMadeJpeg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Put output in a cleaner location
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE HOMEMADE_JPEG_SRCS src/**/*.cpp src/*.cpp)
add_executable(HomeMadeJpeg ${HOMEMADE_JPEG_SRCS})

target_include_directories(HomeMadeJpeg PUBLIC "stb")