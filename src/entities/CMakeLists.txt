add_library(ENTITIES
        Entity.cpp
        )

# Link the relevent include file to the entities library so that the source file can see it.
target_include_directories(ENTITIES PUBLIC ${PROJECT_INCLUDE_DIR}/entities)
target_link_libraries(ENTITIES PUBLIC Vendor)
target_link_libraries(${PROJECT_NAME} PUBLIC ENTITIES)
message(STATUS "Adding Entities done")