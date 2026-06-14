cmake_minimum_required(VERSION 3.16)
project(Ulyses LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.0   # pin to a real release tag
    GIT_SHALLOW TRUE
)

# Build SDL as a static lib; drop tests/examples from the build.
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST   OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3-static)