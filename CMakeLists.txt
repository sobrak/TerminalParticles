cmake_minimum_required(VERSION 3.10)

project(terminalparticles)

add_executable(terminalparticles main.cpp)

install(TARGETS terminalparticles RUNTIME DESTINATION bin)
