cmake_minimum_required(VERSION 3.10)
project(CircuitSimulator)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable and its source files
add_executable(simulator src/main.cpp src/CircuitSimulator.cpp)
