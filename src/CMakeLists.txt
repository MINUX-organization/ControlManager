project(
    ControlManager
    LANGUAGES C CXX
)

#################### INCLUDING ########################
set(
    SOURCES_FILES
    main.cpp
    main.hpp
)

add_subdirectory( communicators )
add_subdirectory( managers )
add_subdirectory( systems )
add_subdirectory( kernel )
add_subdirectory( base )

add_executable(
    ${PROJECT_NAME}
    ${SOURCES_FILES}
)

include_directories(
    "./communicators"
    "./managers"
    "./systems"
    "./kernel"
    "./base"
)

target_link_libraries(
    ${PROJECT_NAME}

    ControlManager-communicators
    ControlManager-managers
    ControlManager-systems
    ControlManager-kernel
    ControlManager-base
)




































