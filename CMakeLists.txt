# command:
# cmake -S ./ -B ./build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

cmake_minimum_required(VERSION 3.28.3)
project(opengl)

set(SRC_DIR ./src/)

set(SRC ${SRC_DIR}main.cpp
    ${SRC_DIR}constants.cpp
    ${SRC_DIR}util.cpp
    ${SRC_DIR}shader.cpp
    ${SRC_DIR}glad.c
)

add_executable(${PROJECT_NAME} ${SRC})

set(EXTLIB_DIR C:/dependencies/)

target_include_directories( ${PROJECT_NAME} 
    PRIVATE ./includes
    PRIVATE ${EXTLIB_DIR}glfw-3.3.9-mingw/build/include
    PRIVATE ${EXTLIB_DIR}glad-cpp-3.3-core/include
    PRIVATE ${EXTLIB_DIR}glm-1.0.0
    PRIVATE ${EXTLIB_DIR}plog-1.1.10/include
)

target_link_libraries( ${PROJECT_NAME} 
    PRIVATE ${EXTLIB_DIR}glfw-3.3.9-mingw/build/lib/libglfw3.a
)