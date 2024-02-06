#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
private:
    unsigned int shader_program{};

    std::string read_shader_file(std::string path);
    unsigned int compile_shader(
        const char* shader_code, 
        GLenum shader_type
    );
    void create_shader_program(
        unsigned int vshader, 
        unsigned int fshader
    );

public:
    Shader();
    Shader(
        std::string vertex_shader_path,
        std::string fragment_shader_path
    );

    unsigned int get_program() const;
    void use_program() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};

#endif