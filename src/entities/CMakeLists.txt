add_library(ENTITIES
        Entity.cpp
        actors/Actor.cpp)

# Link the relevent include file to the entities library so that the source file can see it.
target_include_directories(ENTITIES PUBLIC
        ${PROJECT_INCLUDE_DIR}/entities
        ${PROJECT_INCLUDE_DIR}/entities/actors)
target_link_libraries(ENTITIES PUBLIC Vendor Utilities)
target_link_libraries(${PROJECT_NAME} PUBLIC ENTITIES)
message(STATUS "Adding Entities done")