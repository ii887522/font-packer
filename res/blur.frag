#version 460 core

in vec2 fTexCoord;

out float oColor;

layout(location = 1) uniform sampler2D tex;
layout(location = 2) uniform bool isHorizontal;

const float intensity = 2;

const float weights[] = float[](
  0.2023600146101466,
  0.1790438646174162,
  0.1240093299792275,
  0.06723453549491201,
  0.02853226260337099
);

float blurHorizontally() {
  const float texOffset = 1 / float(textureSize(tex, 0).x);
  float result = texture(tex, fTexCoord).r * weights[0];
  for (uint i = 1; i != weights.length(); ++i) {
    result += texture(tex, fTexCoord - vec2(texOffset * i, 0)).r * weights[i];
    result += texture(tex, fTexCoord + vec2(texOffset * i, 0)).r * weights[i];
  }
  return result;
}

float blurVertically() {
  const float texOffset = 1 / float(textureSize(tex, 0).y);
  float result = texture(tex, fTexCoord).r * weights[0];
  for (uint i = 1; i != weights.length(); ++i) {
    result += texture(tex, fTexCoord - vec2(0, texOffset * i)).r * weights[i];
    result += texture(tex, fTexCoord + vec2(0, texOffset * i)).r * weights[i];
  }
  return result;
}

void main() {
  if (isHorizontal) {
    oColor = blurHorizontally();
  } else {
    oColor = blurVertically();
  }
}
