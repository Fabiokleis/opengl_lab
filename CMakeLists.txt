cmake_minimum_required(VERSION 3.24)
project(opengl_lab)
set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)

include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glew)

find_package(OpenGL REQUIRED)


target_include_directories(${PROJECT_NAME} 
    PUBLIC dependencies/glfw/include
    PUBLIC dependencies/uglew/include
)

target_link_directories(${PROJECT_NAME} PUBLIC dependencies/glfw/src dependencies/glew/src)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw libglew_static) 

