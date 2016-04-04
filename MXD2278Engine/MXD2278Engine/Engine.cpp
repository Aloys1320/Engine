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

	//Create vector of texture reference
	int textureIds = 0;
	//texture map
	std::map<int, GLuint> textures = std::map<int,GLuint>();
	Texture textureLoader = Texture();
	//Assign textures to map w/ coresponding reference
	textures[0]=(textureLoader.loadTexture("textures/TestTexture.png"));
	textures[1]=(textureLoader.loadTexture("textures/wall.jpg"));
	textures[2]=(textureLoader.loadTexture("textures/dome.png"));
	textures[3]=(textureLoader.loadTexture("textures/rain.png"));

	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



		//Escape exits program
		if (keyIsDown[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		
		//Detect mouse button 1 input (updates textures)
		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1]) {
			textureIds++;
			textureIds = textureIds % textures.size();
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, textures[textureIds]);
		sphere.render();
		glBindVertexArray(0);
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
	if (sphere.buffer("models/sphere.obj"))
		return true;
	return false;
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
}


Engine::~Engine()
{
}
