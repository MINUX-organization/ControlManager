cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-systems
    LANGUAGES C CXX
)

add_subdirectory( informations )
add_subdirectory( masters )
add_subdirectory( shells )

include_directories(
    "./informations"
    "./masters"
    "./shells"
)

add_library(
    ${PROJECT_NAME}

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME}

    ControlManager-systems-informations
    ControlManager-systems-masters
    ControlManager-systems-shells
)
