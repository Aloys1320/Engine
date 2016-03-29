#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
#include "Model.h"

class Engine
{
private:
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shaderManager;
	Model model;
public:
	//Attributes

	//Methods
	bool gameLoop();
	bool init();
	bool bufferModels();
	bool useShaders();
	Engine();
	~Engine();
};

