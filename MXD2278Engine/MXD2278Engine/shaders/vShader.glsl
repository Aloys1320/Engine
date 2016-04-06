#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec2 fragUV;
void main()

{
fragUV = uv;
gl_Position = vec4(position, 1);

}