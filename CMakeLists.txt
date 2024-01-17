cmake_minimum_required(VERSION 3.27)
project(saper)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp)

add_executable(saper ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(saper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

