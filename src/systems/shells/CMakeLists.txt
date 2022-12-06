cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-systems-shells
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    STATIC

    common.hpp
    factories.hpp

    # Headers
    executors/inc/executors.hpp
    commands/inc/abstracts.hpp
    commands/inc/commands.hpp

    # Sources
    executors/src/executors.cpp
    commands/src/abstracts.cpp
    commands/src/commands.cpp
)








