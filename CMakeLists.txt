cmake_minimum_required(VERSION 3.20.0)
project(OpenGL_Tutorial VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(app)
add_subdirectory(include)
add_subdirectory(3rd)

