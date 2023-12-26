#version 300 es

#ifdef GL_FRAGMENT_PRECISION_HIGH
  precision highp float;
#else
  precision mediump float;
#endif

in vec2 texcoord_0;
uniform sampler2D diffuse_sampler;
uniform float time;

out vec4 outcolor;

void main() {
  vec4 texcolor = texture(diffuse_sampler, vec2(texcoord_0.x + time, texcoord_0.y));
  if(texcolor.a < 0.1) {
    discard;
  }

  outcolor = texcolor;
}
