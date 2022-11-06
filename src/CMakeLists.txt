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
add_subdirectory( systems )
add_subdirectory( kernel )

add_executable(
    ${PROJECT_NAME}
    ${SOURCES_FILES}
)

include_directories(
    "./communications"
    "./systems"
    "./kernel"
)

target_link_libraries(
    ${PROJECT_NAME}

    ControlManager-communicators
    ControlManager-systems
    ControlManager-kernel
)




































