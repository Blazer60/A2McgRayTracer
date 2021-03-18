add_library(Entities
        Entity.cpp
        actors/Actor.cpp
        actors/Sphere.cpp
        )

# Link the relevent include file to the entities library so that the source file can see it.
target_include_directories(Entities PUBLIC
        ${PROJECT_INCLUDE_DIR}/entities
        ${PROJECT_INCLUDE_DIR}/entities/actors)
target_link_libraries(Entities PUBLIC Vendor Utilities)
target_link_libraries(${PROJECT_NAME} PUBLIC Entities)
message(STATUS "Adding Entities done")