add_library(glad glad.c)
target_include_directories(glad PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(OpenGL_Tutorial glad)

target_link_libraries(OpenGL_Tutorial ${PROJECT_SOURCE_DIR}/3rd/libglfw3.a)

# Cannot mix two signatures PRIVATE/PUBLIC/INTERFACE with the same target