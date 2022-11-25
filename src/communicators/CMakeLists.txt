cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-communicators
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    STATIC

    common.hpp

    # Headers
    web_interfaces/inc/web_interfaces.hpp
    internets/inc/internets.hpp
    miners/inc/miners.hpp

    # Sources
    web_interfaces/src/web_interfaces.cpp
    internets/src/internets.cpp
    miners/src/miners.cpp
)