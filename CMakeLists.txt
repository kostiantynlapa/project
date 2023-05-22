cmake_minimum_required(VERSION 3.25)
project(final)

set(CMAKE_CXX_STANDARD 17)

add_executable(final main.cpp StoryWriter.h StoryWriter.cpp HelperFunctions.h HelperFunctions.cpp Actor.h Actor.cpp)
