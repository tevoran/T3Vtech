cmake_minimum_required(VERSION 3.16)
project("T3V-engine")

#BASICALLY REALEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
SET(CMAKE_CXX_FLAGS "-g")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)
find_library(SDL2_ttf SDL2_ttf)
find_library(SDL2_image SDL2_image)
find_package(SDL2_image REQUIRED)

#creating the executable of Money Man
include_directories(src/)
file(GLOB_RECURSE "T3V-engine" SRC src/*.cpp)
add_executable(T3V-engine ${T3V-engine})

target_link_libraries(T3V-engine LINK_PRIVATE "${SDL2}")
target_link_libraries(T3V-engine LINK_PRIVATE "${SDL2_ttf}")
target_link_libraries(T3V-engine LINK_PRIVATE "${SDL2_image}")

