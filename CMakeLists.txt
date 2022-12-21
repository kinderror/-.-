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
    Headers/
)

add_executable(maxwell ${PROGRAM_SRCS})
