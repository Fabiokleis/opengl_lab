cmake_minimum_required(VERSION 3.24)
project(opengl_lab)
set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(ONLY_LIBS ON CACHE BOOL "" FORCE)

file(GLOB SOURCE ./src/main.cpp ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/stbi)
add_subdirectory(dependencies/glm)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui)
add_library(IMGUI STATIC)
target_sources(IMGUI
    PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp

    PRIVATE
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)

target_include_directories(IMGUI
    PRIVATE ${IMGUI_DIR}
    PRIVATE ${IMGUI_DIR}/backends
)

find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC dependencies/glfw/include
    PUBLIC dependencies/uglew/include
    PUBLIC dependencies/stbi/include
    PUBLIC dependencies/glm/glm
    PUBLIC dependencies/imgui
    PUBLIC dependencies/imgui/backends
)

target_link_directories(${PROJECT_NAME} PUBLIC dependencies/glfw/src dependencies/glew/src)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw libglew_static glm::glm IMGUI) 

