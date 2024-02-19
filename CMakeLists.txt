# command:
# cmake -S ./ -B ./build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

cmake_minimum_required(VERSION 3.28.3)
project(opengl)

set(EXTLIB_DIR C:/dependencies)

# library paths
set(GLFW_DIR ${EXTLIB_DIR}/glfw-3.3.9-mingw)
set(GLAD_DIR ${EXTLIB_DIR}/glad-cpp-3.3-core)
set(GLM_DIR ${EXTLIB_DIR}/glm-1.0.0)
set(PLOG_DIR ${EXTLIB_DIR}/plog-1.1.10)
set(STBIM_DIR ${EXTLIB_DIR}/stb_image)

set(SRC_DIR ./src)
set( SRC 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/constants.cpp
    ${SRC_DIR}/util.cpp
    ${SRC_DIR}/shader.cpp
    ${GLAD_DIR}/src/glad.c
)
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories( ${PROJECT_NAME} 
    PRIVATE ./includes

    PRIVATE ${GLFW_DIR}/build_x64/include
    PRIVATE ${GLAD_DIR}/include
    PRIVATE ${GLM_DIR}
    PRIVATE ${PLOG_DIR}/include
    PRIVATE ${STBIM_DIR}
)

target_link_directories( ${PROJECT_NAME}
    PRIVATE ${GLFW_DIR}/build_x64/lib
)

target_link_libraries( ${PROJECT_NAME} 
    PRIVATE libglfw3.a
)