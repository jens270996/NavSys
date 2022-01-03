cmake_minimum_required(VERSION 3.10)

add_executable(List_Test MapTest.cpp Map.hpp List.hpp PathFinding.hpp RoadMap.hpp Path.hpp Bus.hpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(List_Test PRIVATE Threads::Threads)
