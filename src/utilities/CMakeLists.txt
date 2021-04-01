add_library(Utilities
        raycast/Ray.cpp
        geometry/Geometry.cpp SceneGenerator.cpp ../../include/utilities/SceneGenerator.h)

target_include_directories(Utilities PUBLIC
        ${PROJECT_INCLUDE_DIR}/utilities
        ${PROJECT_INCLUDE_DIR}/utilities/raycast
        ${PROJECT_INCLUDE_DIR}/utilities/geometry)
target_link_libraries(Utilities PUBLIC Vendor Entities)
target_link_libraries(${PROJECT_NAME} PUBLIC Vendor)

message(STATUS "Adding Utilities done")