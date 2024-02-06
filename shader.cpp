#include <glad/glad.h> 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <plog/Log.h>

#include "shader.hpp"

std::string Shader::read_shader_file(std::string path) {
    std::string shader_code{};
    std::ifstream shader_file{};
    shader_file.exceptions(
        std::ifstream::failbit | std::ifstream::badbit
    );

    try {
        shader_file.open(path.c_str());
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();

        shader_code = shader_stream.str();
    }
    catch (std::ifstream::failure e) {
        PLOGD << "failed to read file: \"" << path << '"';
        shader_code =  nullptr;
    }

    return shader_code;
}

unsigned int Shader::compile_shader(
    const char* shader_code, 
    GLenum shader_type
) {
    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    int success{};
    char info_log[512]{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::string t{};
        if (shader_type == GL_VERTEX_SHADER) t = "vertex";
        else if (shader_type == GL_FRAGMENT_SHADER) t = "fragment";
        else t = shader_type;
        PLOGD << "failed to compile shader \"" << t << '"';
        PLOGD << info_log;
    };

    return shader;
}

void Shader::create_shader_program(
    unsigned int vshader, 
    unsigned int fshader
) {
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vshader);
    glAttachShader(shader_program, fshader);
    glLinkProgram(shader_program);

    int success;
    char info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        PLOGD << "failed to create shader program";
        PLOGD << info_log;
    }

    glDeleteShader(vshader);
    glDeleteShader(fshader);
}

Shader::Shader() {};

Shader::Shader(
    std::string vertex_shader_path,
    std::string fragment_shader_path
) {
    std::string vshader_code{};
    unsigned int vshader{};
    vshader_code = read_shader_file(
        vertex_shader_path.c_str()
    );
    vshader = compile_shader(
        vshader_code.c_str(), 
        GL_VERTEX_SHADER
    );

    std::string fshader_code{};
    unsigned int fshader{};
    fshader_code = read_shader_file(
        fragment_shader_path.c_str()
    );
    fshader = compile_shader(
        fshader_code.c_str(), 
        GL_FRAGMENT_SHADER
    );

    create_shader_program(vshader, fshader);
}

unsigned int Shader::get_program() const {
    return shader_program;
}

void Shader::use_program() const {
    glUseProgram(shader_program);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(
        shader_program, name.c_str()), (int)value
    );
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(
        shader_program, name.c_str()), value
    );
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(
        shader_program, name.c_str()), value
    );
}
