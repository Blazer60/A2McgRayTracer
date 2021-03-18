add_library(Utilities
        raycast/Ray.cpp
        )

target_include_directories(Utilities PUBLIC
        ${PROJECT_INCLUDE_DIR}/utilities
        ${PROJECT_INCLUDE_DIR}/utilities/raycast)
target_link_libraries(Utilities PUBLIC Vendor)
target_link_libraries(${PROJECT_NAME} PUBLIC Vendor)

message(STATUS "Adding Utilities done")