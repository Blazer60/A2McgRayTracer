#
# Allows our project to interact with GLM, MCG_GFX and SDL2 when desired.
# Make sure to use "add_subdirectory()" after creating the executable.
#

# SDL2 contains their own main function which can cause conflict with ours.
# It can be disabled with this command.
add_definitions(-DSDL_MAIN_HANDLED)

add_library(Vendor MCG_GFX/MCG_GFX_Lib.cpp)

# The Vendor Dir is also added to make sure that existing file includes also work.
target_include_directories(Vendor PUBLIC MCG_GFX GLM SDL2/include ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC MCG_GFX GLM SDL2/include ${CMAKE_CURRENT_LIST_DIR})

# Look for the SDL2 library recursively within the specified folder.
find_library(SDL_LIB SDL2 ${CMAKE_CURRENT_LIST_DIR}/SDL2/x86)
message(STATUS "SDL Lib Found at: " ${SDL_LIB})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL_LIB} Vendor)


message(STATUS "Adding Vendors done")

