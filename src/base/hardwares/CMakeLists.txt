cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-base-hardwares
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    common.hpp
    factories.hpp

    # Headers
    cpus/inc/cpus.hpp
    gpus/inc/gpus.hpp
    motherboards/inc/motherboards.hpp

    # Sources
    cpus/src/cpus.cpp
    gpus/src/gpus.cpp
    motherboards/src/motherboards.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
)