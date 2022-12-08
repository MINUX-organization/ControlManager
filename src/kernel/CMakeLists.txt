cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-kernel
    LANGUAGES C CXX
)

set( Boost_USE_STATIC_RUNTIME ON ) 
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_LIBS ON ) 

find_package( Threads REQUIRED )
find_package( Boost REQUIRED )

add_subdirectory( sockets )
add_subdirectory( exceptions)

include_directories(
    ${Boost_INCLUDE_DIRS}
    "./sockets"
    "./exceptions"

    /usr/local/include
)

add_definitions(
    -D__FLATJSON__CHILDS_TYPE=std::uint32_t
    -D__FLATJSON__VLEN_TYPE=std::uint32_t
    -DDTF_HEADER_ONLY
    -UNDEBUG
)

add_library(
    ${PROJECT_NAME}

    common.hpp
)

target_link_libraries(
    ${PROJECT_NAME}

    ${Boost_LIBRARIES}

    Threads::Threads

    ControlManager-kernel-sockets
    ControlManager-kernel-exceptions
)
















