add_library(Renderer
        RayTracer.cpp
        )

target_include_directories(Renderer PUBLIC
        ${PROJECT_INCLUDE_DIR}/renderer)
target_link_libraries(Renderer PUBLIC Entities Utilities Vendor)
target_link_libraries(${PROJECT_NAME} PUBLIC Renderer)
message(STATUS "Adding Renderer done")