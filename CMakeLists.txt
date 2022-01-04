cmake_minimum_required(VERSION 3.10)

add_executable(BusRouter MapTest.cpp Map.hpp List.hpp PathFinding.hpp RoadMap.hpp Path.hpp Bus.hpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(BusRouter PRIVATE Threads::Threads)
