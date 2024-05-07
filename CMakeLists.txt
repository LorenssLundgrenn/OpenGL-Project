cmake_minimum_required(VERSION 3.28.3)
set(PROJ_NAME opengl)
project(${PROJ_NAME})

set(SRC_DIR ./src)
set(SRC 
    ${SRC_DIR}/glad.c
    ${SRC_DIR}/stb_image.cpp

    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/constants.cpp
    ${SRC_DIR}/util.cpp
    ${SRC_DIR}/shader.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ./include
    PRIVATE ./include/glad
    PRIVATE ./include/stb_image
)

set(GLFW_DIR "C:/Program Files (x86)/GLFW")
list(APPEND CMAKE_PREFIX_PATH ${GLFW_DIR})
find_package(glfw3 3.3.9 REQUIRED)
find_package(glm 1.0.0 REQUIRED)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE glfw
    PRIVATE glm::glm
)
