#version 430

layout (location = 0) in vec3 position;
out vec2 fragUV;
void main()

{
fragUV = position.xy;
gl_Position = vec4(position, 1);

}