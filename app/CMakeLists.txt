set(PRJ_SRC_CODES 
    glSpace.cpp
    shader.cpp
    main.cpp)

add_executable(OpenGL_Tutorial ${PRJ_SRC_CODES}) 


target_link_libraries(OpenGL_Tutorial GL)
