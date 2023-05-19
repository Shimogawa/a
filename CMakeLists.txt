cmake_minimum_required(VERSION 3.23)
project(logl)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_C_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_SRC_DIR ${CMAKE_SOURCE_DIR}/lib/imgui)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/include/*.hpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glm)

include_directories(
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/imgui"
)

add_executable(logl ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(logl PRIVATE glfw glm)
