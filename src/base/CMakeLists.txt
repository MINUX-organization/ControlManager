cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-base
    LANGUAGES C CXX
)

add_subdirectory( hardwares )

include_directories(
    "./hardwares"
)

add_library(
    ${PROJECT_NAME}

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME}

    ControlManager-base-hardwares
)