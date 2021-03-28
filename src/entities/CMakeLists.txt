add_library(Entities
        Entity.cpp
        actors/Actor.cpp
        actors/Sphere.cpp
        Camera.cpp ../../include/entities/Camera.h

        lights/LightSource.cpp ${PROJECT_INCLUDE_DIR}/entities/lights/LightSource.h
        lights/DirectionalLight.cpp ../../include/entities/lights/DirectionalLight.h)

# Link the relevent include file to the entities library so that the source file can see it.
target_include_directories(Entities PUBLIC
        ${PROJECT_INCLUDE_DIR}/entities
        ${PROJECT_INCLUDE_DIR}/entities/actors
        ${PROJECT_INCLUDE_DIR}/entities/lights)
target_link_libraries(Entities PUBLIC Vendor Utilities)
target_link_libraries(${PROJECT_NAME} PUBLIC Entities)
message(STATUS "Adding Entities done")