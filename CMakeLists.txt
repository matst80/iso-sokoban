cmake_minimum_required(VERSION 3.19)
project(sokoban)

set(CMAKE_CXX_STANDARD 14)

add_executable(sokoban main.cpp LevelLoader.cpp LevelLoader.h Level.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(sokoban ${SFML_LIBRARIES})
endif()