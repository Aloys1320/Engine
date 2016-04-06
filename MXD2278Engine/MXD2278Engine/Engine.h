#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
#include "Model.h"
#include <map>
class Engine
{
private:
	std::map<std::string, Model> models;
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shaderManager;
	Model testModel;
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

