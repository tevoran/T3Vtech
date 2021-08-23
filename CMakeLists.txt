cmake_minimum_required(VERSION 3.16)
project("T3Vtech")

#BASICALLY REALEASE MODE
SET(CMAKE_C_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
#SET(CMAKE_C_FLAGS "-g -ggdb -fsanitize=address")
#SET(CMAKE_C_FLAGS "-g -ggdb")

#PROFILERMODE
#SET(CMAKE_C_FLAGS "-g -pg")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)
find_library(SDL2_ttf SDL2_ttf)
find_library(SDL2_image SDL2_image)
find_package(SDL2_image REQUIRED)

#creating the executable of the engine test
include_directories(src/engine/)
file(GLOB_RECURSE "T3Vtech" SRC src/*.c)
add_executable(T3Vtech ${T3Vtech})

target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2}")
target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_ttf}")
target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_image}")
target_link_libraries(T3Vtech LINK_PRIVATE pthread)
target_link_libraries(T3Vtech LINK_PRIVATE m) #include the std math lib
