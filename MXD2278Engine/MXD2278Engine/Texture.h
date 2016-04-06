#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
class Texture
{
public:
	GLuint texId;

	GLuint loadTexture(char * texturePath);
	Texture(char* );
	Texture();
	~Texture();
};

