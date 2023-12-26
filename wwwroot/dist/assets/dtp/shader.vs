attribute vec3 attrib_pos;
attribute vec2 attrib_texcoord_0;

uniform mat4 mat_proj;
uniform mat4 mat_view;
uniform mat4 mat_view_proj;
uniform mat4 mat_model;

varying vec2 io_texcoord;

void main() {
  mat4 modelview = mat_view_proj * mat_model;
  gl_Position = modelview * vec4(attrib_pos, 1.0);
  io_texcoord = attrib_texcoord_0;
}
