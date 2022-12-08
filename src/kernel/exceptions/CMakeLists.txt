cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-kernel-exceptions
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    STATIC

    common.hpp

    # Headers
    inc/exceptions.hpp

    # Sources
    src/exceptions.cpp
)
