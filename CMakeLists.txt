cmake_minimum_required(VERSION 3.10)

add_executable(TestM Test.cpp BusUpdateCenter.hpp MapUpdater.hpp RoadInformation.hpp Update.hpp)
# set( CMAKE_CXX_FLAGS "-ftemplate-depth=5000")