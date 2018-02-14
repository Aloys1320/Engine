#include "Engine.h"



#define _USE_MATH_DEFINES
#include <cmath>

namespace {
	std::map<int, bool> keyIsDown;
	std::map<int, bool> keyWasDown;
}
void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods) {
	keyIsDown[button] = action;
}
void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	keyIsDown[key] = action;
}


//Main Engine Loop
int Engine::gameLoop()
{
	glEnable(GL_DEPTH_TEST);


	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	//Get GLFW Time
	currentTime = glfwGetTime();
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		//Update Times
		previousTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;

		//Escape exits program
		if (keyIsDown[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}
		float sens = .005;
		int w = 800, h = 600;
		double x, y;
		glfwGetCursorPos(GLFWwindowPtr, &x, &y);
		glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);
		glfwSwapBuffers(GLFWwindowPtr);
		keyWasDown = keyIsDown;
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

//Initiate the GLFW window
int Engine::init()
{
	if (glfwInit() == GL_FALSE) {
		return 1;
	}
	GLFWwindowPtr = glfwCreateWindow(800, 600, "Matt Dieselman Engine", NULL, NULL);

	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return 2;
	}
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return 3;
	}

	return 0;
}

//Buffer the models using the model class.
int Engine::bufferModels()
{
	return 0;
}

int Engine::createShaders()
{
	if (!shaderManager.createShader("Assets/Shaders/vshader.glsl", "Assets/Shaders/fshader.glsl")) {

		glUseProgram(shaderManager.getShaders(0).getprogram());
		return 0;

	}
	else return 4;
}

//Uses the shadersthat are declared
int Engine::useShaders()
{
	//if (shaderManager.getShaders(0).loadShaders("Assets///Shaders/vShader.glsl", "Assets/Shaders/fShader.glsl")) {
	//	glUseProgram(shaderManager.getShaders(0).getprogram());

	return 0;
	//}
	//return 4;
}

Engine::Engine()
{

}


Engine::~Engine()
{

}
