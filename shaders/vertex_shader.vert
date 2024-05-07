#version 330 core

layout (location = 0) in vec3 attr_pos;
layout (location = 1) in vec3 attr_color;
layout (location = 2) in vec2 attr_texture;

out vec4 vertex_color;
out vec2 vertex_texture;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = transform * vec4(attr_pos, 1.0);
    vertex_color = vec4(attr_color, 1.0);
    vertex_texture = attr_texture;
}