cmake_minimum_required(VERSION 3.10)

project(maxwell)
set(CMAKE_CXX_STANDART 17)

set(PROGRAM_SRCS
    main.cpp
    Particle.cpp
    Column.cpp
    create_gas.cpp
    iterate.cpp
    run_simulation.cpp
)

include_directories(
    Headers/CONSTANTS.h
    Headers/Particle.h
    Headers/Column.h
    Headers/create_gas.h
    Headers/iterate.h
    Headers/run_simulation.h
)

add_executable(maxwell ${PROGRAM_SRCS})
