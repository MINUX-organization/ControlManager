cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-base
    LANGUAGES C CXX
)

add_subdirectory( hardwares )
add_subdirectory( utilities )

include_directories(
    "./hardwares"
    "./utilities"
)

add_library(
    ${PROJECT_NAME}

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME}

    ControlManager-base-hardwares
    ControlManager-base-utilities
)