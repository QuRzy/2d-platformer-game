cmake_minimum_required(VERSION 3.17)
project(2d_platformer)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS graphics audio REQUIRED)
add_executable(2d_platformer main.cpp Player.cpp Player.h SPRITE.cpp SPRITE.h Particle.cpp Particle.h VECTOR.h Enemy.cpp Enemy.h)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(2d_platformer sfml-graphics sfml-audio)