set(PRJ_SRC_CODES
    glLight.cpp
    glSpace.cpp
    shader.cpp
    main.cpp)

add_executable(OpenGL_Tutorial ${PRJ_SRC_CODES}) 


target_link_libraries(OpenGL_Tutorial GL)
