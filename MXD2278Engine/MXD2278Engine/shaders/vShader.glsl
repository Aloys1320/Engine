#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;		//MODEL NORMALS
uniform mat4 worldLoc;
uniform mat4 cameraMat;

out vec2 fragUV;
out vec3 worldMat;	//Output the world matrix (location in world space)
out vec3 worldNormal;	//Output the object normal in the world space

void main()

{
fragUV = uv;
worldMat = vec3(worldLoc * vec4(position,1));
worldNormal = vec3(transpose(inverse(worldLoc)) * vec4(normal, 0));
gl_Position = (cameraMat * (worldLoc * vec4(position,1)));

}