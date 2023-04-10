#version 450

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 inColor;

layout (location = 0) out vec4 outColor;

layout (binding = 0) uniform Buffer
{
    mat4 mvpc;
} uniformBuffer;



void main() {
    outColor = inColor;
    gl_Position = uniformBuffer.mvpc * pos;
}