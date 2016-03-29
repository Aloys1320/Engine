#include "Engine.h"


bool Engine::gameLoop()
{	
	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vertArr);
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
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

bool Engine::bufferModel()
{	
	//Create Quad
	std::vector<glm::vec3> locs = {
		{ .9,.9,0 },		//top Right
		{ -.9,.9,0 },		//Top Left
		{ -.9,-.9,0 },	//Bottom Left
		{ .9,-.9,0 } };	//Bottom Right
	std::vector<unsigned int> locInds = { 0,1,2,0,2,3 };
	vertCount = locInds.size();
	std::vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = locs[locInds[i]];
	}

	//Create & Bind buffer

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertCount, &vertBufData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBindVertexArray(0);
	return true;
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
