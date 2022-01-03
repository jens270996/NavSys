cmake_minimum_required(VERSION 3.10)

add_executable(List_Test MapTest.cpp Map.hpp List.hpp PathFinding.hpp RoadMap.hpp Path.hpp Bus.hpp)
# set( CMAKE_CXX_FLAGS "-ftemplate-depth=5000")