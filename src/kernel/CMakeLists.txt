cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-kernel
    LANGUAGES C CXX
)

find_package( Threads REQUIRED )

add_subdirectory( shells )
add_subdirectory( sockets )

include_directories(
    "./command"
    "./sockets"
    /usr/local/include
)

add_definitions(
    -UNDEBUG
    -DDTF_HEADER_ONLY
    -D__FLATJSON__CHILDS_TYPE=std::uint32_t
    -D__FLATJSON__VLEN_TYPE=std::uint32_t
)

add_library(
    ${PROJECT_NAME}

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME}

    Threads::Threads

    ControlManager-kernel-shell
)
















