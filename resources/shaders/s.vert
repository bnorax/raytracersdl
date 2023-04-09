#version 450

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 inColor;

layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform Buffer
{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat4 clip;
} uniformBuffer;



void main() {
    outColor = inColor;
    mat4 mvp = uniformBuffer.model * uniformBuffer.view * uniformBuffer.projection * uniformBuffer.clip;
    gl_Position = mvp * pos;
}