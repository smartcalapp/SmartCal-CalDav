cmake_minimum_required(VERSION 3.12)
project(SmartCal_CalDav)

set(CMAKE_CXX_STANDARD 14)

add_executable(SmartCal_CalDav src/main.cpp src/net/socket.cpp src/webDav/webDav.cpp src/webDav/webDav.h)