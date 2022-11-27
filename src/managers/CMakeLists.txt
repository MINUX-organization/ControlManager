cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-managers
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    common.hpp

    # Headers
    gpus/inc/gpus.hpp
    statistics/inc/abstracts.hpp
    statistics/inc/statistics.hpp
    commanders/inc/commanders.hpp
    informations/inc/informations.hpp

    # Sources
    gpus/src/gpus.cpp
    statistics/src/abstracts.cpp
    statistics/src/statistics.cpp
    commanders/src/commanders.cpp
    informations/src/informations.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
)