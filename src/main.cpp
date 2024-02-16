#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

#include "constants.hpp"
#include "util.hpp"
#include "shader.hpp"
#include "stb_image.hpp"

void handle_fatal_GLFW_error();
int initialize_program();
void framebuffer_size_callback(
    GLFWwindow*,
    int new_width, int new_height
);

void generate_vertex_data();
void clean_up();

void mainloop();
void process_inputs();
void render();

GLFWwindow* window;
Shader shader;
unsigned int VAO{};
unsigned int VBO{};
unsigned int EBO{};
bool wireframe_mode = false;
unsigned int nvertices{};

int main()
{
    if (initialize_program() < 0) {
        return -1;
    }

    shader = Shader(
        VERTEX_SHADER_PATH,
        FRAGMENT_SHADER_PATH
    );
    generate_vertex_data();
    mainloop();
    clean_up();

    return 0;
}

void handle_fatal_GLFW_error() {
    const char* errDesc;
    glfwGetError(&errDesc);
    PLOGD << errDesc;
    glfwTerminate();
}

int initialize_program() {
    // initialize plog
    plog::init(plog::debug, "log.txt");

    // initialize GLFW
    if (!glfwInit()) {
        PLOGD << "failed to initialize GLFW";
        handle_fatal_GLFW_error();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__ // mac OS compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create window
    window = glfwCreateWindow(
        INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT,
        WIN_TITLE, NULL, NULL
    );
    if (!window) {
        PLOGD << "failed to create window";
        handle_fatal_GLFW_error();
        return -1;
    }
    glfwSetWindowSizeLimits(window,
        MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT,
        GLFW_DONT_CARE, GLFW_DONT_CARE
    );
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // initialize GLAD function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PLOGD << "failed to initialize GLAD function pointers";
        glfwTerminate();
        return -1;
    }

    return 0;
}

// update viewport upon window resize
void framebuffer_size_callback(
    GLFWwindow*, // callback arg
    int new_width, int new_height
) {
    glViewport(0, 0, new_width, new_height);
}

void generate_vertex_data() {
    // primitive vertex data
    float vertices[] = {
        // vertex coordinates // vertex colors  // texture mapping
        // front
        -0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,   // 0 top left
         0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 1 top right
         0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,   // 2 bottom right
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // 3 bottom left
        // back
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // 4 top left
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // 5 top right
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // 6 bottom right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // 7 bottom left
    };

    // specify order of drawing vertices
    unsigned int indices[] = {
        // front face
        0, 1, 2,
        0, 3, 2,
        // back face
        4, 5, 6,
        4, 7, 6,
        // top face
        0, 1, 4,
        1, 4, 5,
        // bottom face
        3, 2, 6,
        3, 7, 6,
        // left face
        0, 3, 7,
        0, 4, 7,
        // right face
        1, 2, 6,
        1, 5, 6
    };
    // number of indices is the same as number of
    // vertices in this case
    nvertices = sizeof(indices) / sizeof(unsigned int);

    // store following state configurations
    // for VBO and EBO objects in this VAO 
    // between VAO bind and unbind calls
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate vertex buffer, bind array buffer
    // target to VBO and set buffer data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(vertices),
        vertices, GL_STATIC_DRAW
    );

    // generate element buffer, bind element array
    // buffer target to EBO and set buffer data
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
        indices, GL_STATIC_DRAW
    );

    // we link vertex data, vertex color data, and
    // vertex texture data using pointers to the
    // vertex buffer object

    // specify location of vertex data attributes and
    // enable attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
        8 * sizeof(float), (void*)0
    );
    glEnableVertexAttribArray(0);

    // specify location of vertex color data attributes
    // and enable attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
        8 * sizeof(float), (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // specify location of vertex texture data attributes
    // and enable attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 
        8 * sizeof(float), (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    // unbind VBO, EBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // define texture sampling behaviour
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // define texture scaling behavior
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // define mipmap filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    shader.use_program();
    stbi_set_flip_vertically_on_load(true);

    // generate texture object "container.jpg"
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(CONTAINER_PATH.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        // set buffer data and generate mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glUniform1i(glGetUniformLocation(shader.get_program(), "TBO1"), 0);
    stbi_image_free(data);

    // generate texture object "awesomeface.png"
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // load image
    data = stbi_load(AWESOMEFACE_PATH.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        // set buffer data, generate mipmaps and free image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glUniform1i(glGetUniformLocation(shader.get_program(), "TBO2"), 1);
    stbi_image_free(data);
}

void clean_up() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.get_program());

    glfwDestroyWindow(window);
    glfwTerminate();
}

void mainloop() {
    while (!glfwWindowShouldClose(window))
    {
        process_inputs();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void process_inputs() {
    static bool was_g_pressed = false;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
    else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !was_g_pressed) {
        was_g_pressed = true;
        wireframe_mode = !wireframe_mode;
        if (wireframe_mode) {
            // draw polygons as lines
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            // fill faces of polygons
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_G) != GLFW_PRESS) {
        was_g_pressed = false;
    }
}

void render() {
    glClearColor(BLACK[0], BLACK[1], BLACK[2], BLACK[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use_program();

    // continually change GLSL "color" attribute
    std::vector<float> color = oscillate_rgb(glfwGetTime());
    int color_uniform_location = glGetUniformLocation(
        shader.get_program(), "color"
    );
    glUniform4f(color_uniform_location,
        color[0], color[1], color[2], 1.0f
    );

    // scale and rotate vertex data
    // matrix multiplication is read right to left
    glm::mat4 model = glm::mat4(1.0f);
    std::vector<float> rgb = oscillate_rgb(glfwGetTime());
    model = glm::rotate(model, (float)(sin(glfwGetTime())+5+glfwGetTime()), glm::vec3(rgb[0], rgb[1], rgb[2]));
    unsigned int trans_loc = glGetUniformLocation(shader.get_program(), "transform");
    glUniformMatrix4fv(trans_loc, 1, GL_FALSE, glm::value_ptr(model));

    // render triangle using previously
    // defined VBO and EBO vertex data
    // by binding to the corresponding VAO
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, nvertices, GL_UNSIGNED_INT, 0);
}