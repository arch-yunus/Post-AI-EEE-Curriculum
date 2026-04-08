cmake_minimum_required(VERSION 3.10)
project(RTOS_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Threads library for OS level multi-threading
find_package(Threads REQUIRED)

add_executable(rtos_sim src/main.cpp)
target_link_libraries(rtos_sim Threads::Threads)
