cmake_minimum_required( VERSION 3.1.0 )

project(
    ControlManager-systems-gpu_masters
    LANGUAGES C CXX
)

set( NVCtrlLib_FOUND false )
set( NVCtrlLib_INCLUDE_DIR )
set( NVCtrlLib_LIBRARY )


find_package(
    X11 REQUIRED
)
find_library(
    NVCtrlLib_LIBRARY 
    XNVCtrl 
    /usr/lib
    DOC "Path to NVCONTROL static library (libXNVCtrl.a)"
)
find_path(
    NVCtrlLib_INCLUDE_DIR 
    NVCtrlLib.h 
    /usr/include/NVCtrl
    DOC "Path to NVCONTROL headers (NVCtrlLib.h and NVCtrl.h)"
)

if( NVCtrlLib_LIBRARY AND NVCtrlLib_INCLUDE_DIR )
    set( NVCtrlLib_FOUND true )
endif()

include_directories(
    ${X11_INCLUDE_DIR}
    ${NVCtrlLib_INCLUDE_DIR}
)

link_directories(
    ${X11_LIBRARIES}
    ${NVCtrlLib_LIBRARY}
)

add_library(
    ${PROJECT_NAME}

    STATIC

    common.hpp

    # Headers
    amds/inc/amds.hpp
    nvidias/inc/nvidias.hpp

    # Sources
    amds/src/amds.cpp
    nvidias/src/nvidias.cpp
)

target_link_libraries(
    ${PROJECT_NAME} 

    ${NVCtrlLib_LIBRARY}
    ${X11_LIBRARIES}
)