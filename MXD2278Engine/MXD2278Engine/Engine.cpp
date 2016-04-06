#include "Engine.h"
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

	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



		//Escape exits program
		if (keyIsDown[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		
		//Detect mouse button 1 input (updates textures)
		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1]) {
			testModel.updateTexture();
		}
		glClear(GL_COLOR_BUFFER_BIT);
		testModel.render();

		for each (std::pair<std::string,Model> mod in models)
		{
			//std::cout<<mod.first<<std::endl;
			//mod.second.render();
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
	for each (std::pair<std::string, Model> mod in models)
	{
		if (!mod.second.buffer(mod.second.getFilePath())){
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
	models = std::map<std::string, Model>();
	models["box"] = Model("models/box.obj");


}


Engine::~Engine()
{
}
