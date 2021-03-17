cmake_minimum_required(VERSION 3.17)
project(A2McgRayTracer)

set(CMAKE_CXX_STANDARD 14)
# SDL2 contains their own main function which can cause conflict with ours. It can be disabled with this command.
add_definitions(-DSDL_MAIN_HANDLED)

# Set up the mcg Framework.
include(vendor/MCG_GFX/CMakeLists.txt)

# Let's us use the header files within our program.
link_directories(${CMAKE_SOURCE_DIR}/include/SDL2)


# includes to make "#include" management much easier.
# E.g.: #include "../../../vendor/SDL/include/SDL.h" could appear.
include_directories(A2McgRayTracer
        vendor
        vendor/GLM
        vendor/SDL2/include
        )

add_executable(A2McgRayTracer
        src/main.cpp
        )

# Look for the SDL2 library recursively within the specified folder.
find_library(SDL_LIB SDL2 ${CMAKE_SOURCE_DIR}/vendor/SDL2/x86)

# Tell us what it found and assigned to the variable.
message(STATUS "SDL Lib Found at: " ${SDL_LIB})

# Add to the path so that the executable can compile correctly.
target_link_libraries(A2McgRayTracer
        ${SDL_LIB}
        McgFramework
        )

# Copies over all of library files that are required to build the program.
add_custom_command(TARGET A2McgRayTracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/vendor/SDL2/x86/dll"
        "$<TARGET_FILE_DIR:A2McgRayTracer>"
        )