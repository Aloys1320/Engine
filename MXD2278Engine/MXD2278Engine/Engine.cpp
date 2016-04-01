#include "Engine.h"
#include <map>
#include <list>
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
bool Engine::gameLoop()
{

	//Use functions
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	//Create vector of textures
	int textureIds = 0;
	std::vector<Texture> textures = std::vector<Texture>();

	//Assign textures to vector
	textures.push_back(Texture("textures/TestTexture.png"));
	textures.push_back(Texture("textures/wall.jpg"));
	textures.push_back(Texture("textures/dome.png"));
	textures.push_back(Texture("textures/rain.png"));

	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		keyWasDown = keyIsDown;

		glfwPollEvents();

		if (keyIsDown[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1]) {
			textureIds++;
			textureIds = textureIds % textures.size();
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, textures[textureIds].texId);
		model.render();
		glBindVertexArray(0);
		glfwSwapBuffers(GLFWwindowPtr);
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
