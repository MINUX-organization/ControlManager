cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-managers
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    common.hpp
    factories.hpp

    # Headers
    gpus/inc/gpus.hpp
    cpus/inc/cpus.hpp
    motherboards/inc/motherboards.hpp

    # Sources
    gpus/src/gpus.cpp
    cpus/src/cpus.cpp
    motherboards/src/motherboards.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
)