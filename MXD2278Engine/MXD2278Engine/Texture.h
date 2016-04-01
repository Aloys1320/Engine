#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
#include "Model.h"
class Texture
{
public:
	GLuint texId;
	Texture();
	Texture(char* filePath);
	~Texture();
};

