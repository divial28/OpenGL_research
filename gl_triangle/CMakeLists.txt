cmake_minimum_required(VERSION 3.0.0)

project(glTriangle)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(glTriangle sfml-graphics sfml-audio ${OPENGL_LIBRARY} ${GLEW_LIBRARY})