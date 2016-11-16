#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
#include "ShaderManager.h"
#include "Model.h"
#include <map>
#include "GameObject.h"
#include "Camera.h"

class Engine
{
private:
	std::map<std::string, GameObject> gameObjects;
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shaderManager;
	Model testModel;
	GameObject playButton;

	float currentTime;
	float previousTime;
	float deltaTime;
	glm::mat4 cameraLoc;
	Camera mainCamera;
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

