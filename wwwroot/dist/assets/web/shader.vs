#version 300 es

layout (location = 0) in vec3 attrib_pos;
layout (location = 1) in vec2 attrib_texcoord_0;

uniform mat4 mat_proj;
uniform mat4 mat_model;

out vec2 texcoord_0;

void main() {
  mat4 modelview = mat_proj * mat_model;
  gl_Position = modelview * vec4(attrib_pos, 1.0);
  texcoord_0 = attrib_texcoord_0;
}
