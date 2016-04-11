#include "Engine.h"
#include <glm/gtx/transform.hpp>

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
bool Engine::gameLoop()
{

	//Use functions
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	gameObjects["wall"].model.loadTexture("wall","textures/wall.jpg");
	gameObjects["wall2"].model.loadTexture("wall", "textures/wall.jpg");
	gameObjects["goal"].model.loadTexture("goal", "textures/goal.jpg");
	gameObjects["obs"].model.loadTexture("spike", "textures/spike.jpg");
	gameObjects["obs2"].model.loadTexture("spike", "textures/spike.jpg");
	gameObjects["player"].model.loadTexture("player", "textures/mario.png");

	glm::mat4 translate;

	for (auto& mod : gameObjects)
	{
		translate = { 1, 0, 0, mod.second.transform.location.x,
			0, 1, 0, mod.second.transform.location.y,
			0, 0, 1, mod.second.transform.location.z,
			0, 0, 0, 1 };
		//std::cout<<mod.first<<std::endl;
		mod.second.transform.worldTrans = glm::scale(mod.second.transform.worldTrans, mod.second.transform.size) *
			glm::yawPitchRoll(mod.second.transform.rotation.y, mod.second.transform.rotation.x, mod.second.transform.rotation.z) * translate;
		//glm::translate(mod.second.transform.location);
	}

	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



		//Escape exits program
		if (keyIsDown[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		
		//Detect mouse button 1 input (updates textures)
		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1]) {
			//testModel.updateTexture();
			for (auto& mod : gameObjects)
			{
				//std::cout<<mod.first<<std::endl;
				mod.second.model.updateTexture();
			}

		}
		glClear(GL_COLOR_BUFFER_BIT);



		//RENDER SECTION
		//testModel.render();

		GLint variable = glGetUniformLocation(shaderManager.getprogram(), "worldLoc");

		for (auto& mod : gameObjects)
		{
			//std::cout<< <<std::endl;
			//glUniformMatrix4fv(3, 1, GL_FALSE, &mod.second.transform.worldTrans[0][0]);
			glProgramUniformMatrix4fv(shaderManager.getprogram(), variable, 1, GL_FALSE, &mod.second.transform.worldTrans[0][0]);
			mod.second.model.render();
		}

		//Swap bufferes around to draw items on screen
		glfwSwapBuffers(GLFWwindowPtr);
		//Update old keypresses 
		keyWasDown = keyIsDown;
		//Get key updates
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

//Buffer the models using the modelclass.
bool Engine::bufferModels()
{
	//Attempt to buffer the test model
	if (!(testModel.buffer("models/sphere.obj"))) {
		std::cout << "Failed to buffer test model" << std::endl;
		return false;
	}
	else { std::cout << "Loaded Test Model" << std::endl; }
	//Buffer all models
	for(auto& mod : gameObjects)
	{
		if (
			!mod.second.model.buffer(
				mod.second.model.getFilePath()
				)
			){
			std::cout << "Failed to load model: " << mod.first << std::endl;
			return false;
		}
		else {
			std::cout << "Loaded model: " << mod.first << std::endl;
		}
	}


	return true;
}

//Uses the shadersthat are declared
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
	gameObjects = std::map<std::string, GameObject>();
	gameObjects["wall"].model = Model("models/box.obj");
	gameObjects["wall"].transform = {
		glm::vec3(0,.8, 0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(2,.6,0),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["wall2"].model = Model("models/box.obj");
	gameObjects["wall2"].transform = {
		glm::vec3(0,-.7,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(2,.8,0),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["goal"].model = Model("models/box.obj");
	gameObjects["goal"].transform = {
		glm::vec3(.8,0,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.5,.5,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["player"].model = Model("models/box.obj");
	gameObjects["player"].transform = {
		glm::vec3(-.8,0,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.5,.5,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["obs"].model = Model("models/box.obj");
	gameObjects["obs"].transform = {
		glm::vec3(-.4,.4,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.1,.1,.1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["obs2"].model = Model("models/box.obj");
	gameObjects["obs2"].transform = {
		glm::vec3(.3,.4,1),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.1,.1,.1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};

}


Engine::~Engine()
{

}
