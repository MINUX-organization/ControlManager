cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-systems-masters
    LANGUAGES C CXX
)

add_subdirectory( gpus )

include_directories(
    "./gpus"
)

add_library(
    ${PROJECT_NAME}

    STATIC

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME} 

    ControlManager-systems-masters-gpus
)