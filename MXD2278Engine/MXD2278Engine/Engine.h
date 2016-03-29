#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
class Engine
{
private:
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr;
	GLuint vertBuf;
	unsigned int vertCount;
	ShaderManager shaderManager;
public:
	//Attributes

	//Methods
	bool gameLoop();
	bool init();
	bool bufferModel();
	bool useShaders();
	Engine();
	~Engine();
};

