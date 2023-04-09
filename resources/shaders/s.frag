#version 450
layout (location = 0) in vec4 color;
layout (location = 0) out vec4 outColor;
void main()
{
  outColor = vec4(color.x, color.y, color.z, 1.0f);
}