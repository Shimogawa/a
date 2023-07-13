cmake_minimum_required(VERSION 3.14)
project(logl)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_C_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_SRC_DIR ${CMAKE_SOURCE_DIR}/lib/imgui)

add_compile_definitions(_HAS_EXCEPTIONS=0)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/include/*.hpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/fmt)

include_directories(
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/imgui"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm fmt)

