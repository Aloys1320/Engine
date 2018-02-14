#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
#include <map>
#include "ShaderManager.h"
#include <glm/gtx/transform.hpp>
#include "Camera.h"
class Engine
{
private:
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shaderManager;
	float currentTime;
	float previousTime;
	float deltaTime;
	Camera mainCamera;
public:
	int gameLoop();
	int init();
	int bufferModels();
	int createShaders();
	int useShaders();
	Engine();
	~Engine();
};

