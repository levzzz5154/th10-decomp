cmake_minimum_required(VERSION 3.14)
project(th10_decomp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(SDL2)
find_package(SDL2_mixer)
find_package(OpenGL)

# Engine library
file(GLOB_RECURSE ENGINE_SOURCES
    src/core/*.cpp
    src/render/*.cpp
    src/audio/*.cpp
    src/input/*.cpp
    src/game/*.cpp
    src/data/*.cpp
    src/vm/*.cpp
    src/util/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
    include/*.h
)

add_library(th10_engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_include_directories(th10_engine PUBLIC include)
target_link_libraries(th10_engine
    PUBLIC
    SDL2::SDL2
    SDL2_mixer::SDL2_mixer
    OpenGL::GL
)

# Main executable
add_executable(th10
    src/main.cpp
)
target_include_directories(th10 PRIVATE src src/core src/data src/vm)
target_link_libraries(th10 PRIVATE th10_engine)

# Tools
add_subdirectory(tools)
