cmake_minimum_required(VERSION 3.10)
project(BMS_Firmware)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bms_sim 
    src/main.cpp
    src/BMS_Controller.cpp
)
