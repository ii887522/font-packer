#version 460 core

in vec2 fTexCoord;

out vec4 oColor;

layout(location = 1) uniform sampler2D tex;

void main() {
  oColor = vec4(1, 1, 1, texture(tex, fTexCoord).r);
}
