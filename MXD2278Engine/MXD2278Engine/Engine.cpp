#include "Engine.h"

bool Engine::gameLoop()
{

	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glClear(GL_COLOR_BUFFER_BIT);
		model.render();
		glBindVertexArray(0);
		glfwSwapBuffers(GLFWwindowPtr);
		glfwPollEvents();
	}
	glfwTerminate();
	return true;
}

//Initiate the GLFW window
bool Engine::init()
{
	if (glfwInit() == GL_FALSE) {
		return false;
	}

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Matt Dieselman DSA1 Engine", NULL, NULL);

	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return false;
	}
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}
	return true;
}

bool Engine::bufferModels()
{	
	if (model.buffer("models/sphere.obj"))
		return true;
	return false;
}

bool Engine::useShaders()
{
	if (shaderManager.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl")) {
		glUseProgram(shaderManager.getprogram());
		return true;
	}
	return false;
}

Engine::Engine()
{
}


Engine::~Engine()
{
}
