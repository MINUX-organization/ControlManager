cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-base-utilities
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    common.hpp

    # Headers
    commanders/inc/commanders.hpp

    # Sources
    commanders/src/commanders.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
)