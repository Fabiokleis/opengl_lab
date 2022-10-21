cmake_minimum_required(VERSION 3.24)
project(opengl_lab)
set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(dependencies/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC dependencies/glfw/include
)

target_link_directories(${PROJECT_NAME} PUBLIC dependencies/glfw/src)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)

