#version 300 es

#ifdef GL_FRAGMENT_PRECISION_HIGH
  precision highp float;
#else
  precision mediump float;
#endif

in vec4 vertex_col;
in vec2 texcoord_0;
uniform sampler2D tank_sampler;

out vec4 outcolor;

void main() {
  vec4 texcolor = vec4(vertex_col.rgb, texture(tank_sampler, texcoord_0).a);
  outcolor = texcolor;
}

