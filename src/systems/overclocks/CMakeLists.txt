cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-systems-overclocks
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    STATIC

    common.hpp

    # Headers
    amds/inc/amds.hpp
    nvidias/inc/nvidias.hpp

    # Sources
    amds/src/amds.cpp
    nvidias/src/nvidias.cpp
)