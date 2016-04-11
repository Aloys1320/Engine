#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
uniform mat4 worldLoc;
out vec2 fragUV;
void main()

{
fragUV = uv;
vec4 worldLocVec = vec4(position,1) * worldLoc;
gl_Position = worldLocVec;

}