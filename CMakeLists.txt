cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD  14)
set(PROJECT_NAME        A2McgRayTracer)
set(MAIN_SOURCE_DIR     ${CMAKE_SOURCE_DIR}/src/Main.cpp)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
        ${MAIN_SOURCE_DIR}
        )

# Add all third-party libraries
add_subdirectory(vendor)

# Copies over all of SDL2 library dlls that are required for the program to run.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/vendor/SDL2/x86/dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        )