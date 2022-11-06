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

add_subdirectory( kernel )

add_executable(
    ${PROJECT_NAME}
    ${SOURCES_FILES}
)

include_directories(
    "./kernel"
)

target_link_libraries(
    ${PROJECT_NAME}

    ControlManager-kernel
)




































