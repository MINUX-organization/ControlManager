cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-kernel-shell
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    STATIC

    # Headers
    commands/inc/abstracts.hpp
    commands/inc/commands.hpp
    executors/inc/executors.hpp

    # Sources
    commands/src/abstracts.cpp
    commands/src/commands.cpp
    executors/src/executors.cpp
)








