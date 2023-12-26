varying vec2 io_texcoord;

uniform sampler2D diffuse_sampler;
uniform float time;

void main() {
  vec4 texcolor = texture2D(diffuse_sampler, vec2(io_texcoord.x + time, io_texcoord.y));
  if(texcolor.a < 0.1) {
    discard;
  }

  gl_FragColor = texcolor;
}
