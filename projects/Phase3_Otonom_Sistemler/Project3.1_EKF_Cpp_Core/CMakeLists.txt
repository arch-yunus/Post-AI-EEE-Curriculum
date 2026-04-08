cmake_minimum_required(VERSION 3.10)
project(EKF_Cpp_Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ekf_sim 
    src/main.cpp
    src/EKF.cpp
)
