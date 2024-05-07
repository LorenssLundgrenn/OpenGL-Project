#version 330 core

in vec4 vertex_color;
in vec2 vertex_texture;

out vec4 fragment_color;

uniform vec4 color;
// texture buffer objects
uniform sampler2D TBO1; 
uniform sampler2D TBO2;

void main() {
   vec4 texture1 = texture(TBO1, vertex_texture);
   vec4 texture2 = texture(TBO2, vertex_texture);
   fragment_color = mix(texture1, texture2, 0.2);
   fragment_color *= color;
   fragment_color = color;
}