cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-managers
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    # Headers
    gpus/inc/gpus.hpp
    statistics/inc/abstracts.hpp
    statistics/inc/statistics.hpp
    web_interfaces/inc/web_interfaces.hpp

    # Sources
    gpus/src/gpus.cpp
    statistics/src/abstracts.cpp
    statistics/src/statistics.cpp
    web_interfaces/src/web_interfaces.cpp

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME}
)