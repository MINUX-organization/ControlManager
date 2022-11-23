cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-kernel-sockets
    LANGUAGES C CXX
)

add_library(
    ${PROJECT_NAME}

    STATIC

    # Headers
    ./clients/inc/clients.hpp
    ./servers/inc/servers.hpp

    # Sources
    ./clients/src/clients.cpp
    ./servers/src/servers.cpp
)
