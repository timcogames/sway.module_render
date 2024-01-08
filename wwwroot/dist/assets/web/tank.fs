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
  // vec4 texcolor = vec4(vertex_col.xyz, texture(crate_sampler, texcoord_0).a);
  vec4 texcolor = texture(tank_sampler, texcoord_0);
  if(texcolor.a < 0.1) {
    discard;
  }

  outcolor = texcolor;
}