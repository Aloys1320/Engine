#include "Engine.h"
#include <glm/gtx/transform.hpp>


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
bool Engine::gameLoop()
{
	glEnable(GL_DEPTH_TEST);

	mainCamera.camTransform.location = glm::vec3(0, 0, 2);
	//Use functions
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	//Set Textures for Game Objects
	gameObjects["wall"].model.loadTexture("wall","textures/wall.jpg");
	gameObjects["wall2"].model.loadTexture("wall", "textures/wall.jpg");
	gameObjects["goal"].model.loadTexture("goal", "textures/goal.jpg");
	gameObjects["obs"].model.loadTexture("spike", "textures/spike.jpg");
	gameObjects["obs2"].model.loadTexture("spike", "textures/spike.jpg");
	gameObjects["player"].model.loadTexture("player", "textures/mario.png");


	//Get GLFW Time
	currentTime=glfwGetTime();
	//Game Loop
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		//Update Times
		previousTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;

		//Escape exits program
		if (keyIsDown[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		

		//Character Movement
		if (keyIsDown[GLFW_KEY_D])
			gameObjects["player"].rigidBody.force += glm::vec3(2,0,0);
		if(keyWasDown[GLFW_KEY_D]&&!keyIsDown[GLFW_KEY_D])
			gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);
		if (keyIsDown[GLFW_KEY_A])
			gameObjects["player"].rigidBody.force += glm::vec3(-2, 0, 0);
		if (keyWasDown[GLFW_KEY_A] && !keyIsDown[GLFW_KEY_A])
			gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);


		//Lighting
		glm::vec3 lightLocation = glm::vec3( 4,2,5);
		glUniform3fv(glGetUniformLocation(shaderManager.getprogram(), "lightLoc"), 1, &lightLocation[0]);
		glUniform3fv(glGetUniformLocation(shaderManager.getprogram(), "camLoc"), 1, &mainCamera.camTransform.location[0]);




		//Update Section
		for (auto& mod : gameObjects)
		{
			mod.second.updateModel(shaderManager.getprogram(),deltaTime);
		}
		
		//Collision check
		if (gameObjects["player"].collidesWith(gameObjects["goal"])) {
			std::cout << "Player has collided with the Goal" << std::endl;
			gameObjects["player"].rigidBody.velocity = glm::vec3(0);
		}
		//Camera Update

	//Camera Movement
		//Mouse Detection
		float sens = .005;
		int w = 800, h = 600;
		double x, y;
		glfwGetCursorPos(GLFWwindowPtr, &x, &y);
		mainCamera.camTransform.rotation.y -= sens * (x - w * .5f); // Yaw
		mainCamera.camTransform.rotation.x -= sens * (y - h * .5f); // Pitch
		mainCamera.camTransform.rotation.x =
			glm::clamp(mainCamera.camTransform.rotation.x, -.5f * 3.14f , .5f * 3.14f);
		glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);


		//Key Detection for Camera
		glm::vec3 camVel;
		glm::mat3 R = (glm::mat3)glm::yawPitchRoll(mainCamera.camTransform.rotation.y, mainCamera.camTransform.rotation.x, mainCamera.camTransform.rotation.z);
		if (keyIsDown[GLFW_KEY_LEFT])
			camVel += R * glm::vec3(-10, 0, 0);
		if (keyIsDown[GLFW_KEY_RIGHT])
			camVel += R * glm::vec3(10, 0, 0);
		if (keyIsDown[GLFW_KEY_UP])
			camVel += R * glm::vec3(0, 0, -10);
		if (keyIsDown[GLFW_KEY_DOWN])
			camVel += R * glm::vec3(0, 0, 10);
		float speed = 10.f;
		if (camVel != glm::vec3())
			camVel = glm::normalize(camVel) * speed;
		mainCamera.camRigidBody.force = camVel;
		mainCamera.updateCamera(shaderManager.getprogram(), deltaTime);

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
		/*for (auto& mod : gameObjects)
		{
			mod.second.model.shaderProg = shaderManager.getprogram();
		}*/
		return true;
	}
	return false;
}

Engine::Engine()
{

	//Declare Game Objects (class later?)
	gameObjects = std::map<std::string, GameObject>();
	gameObjects["wall"].model = Model("models/box.obj");
	gameObjects["wall"].transform = {
		glm::vec3(0,1.3, 0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(2,.6,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["wall"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["wall2"].model = Model("models/box.obj");
	gameObjects["wall2"].transform = {
		glm::vec3(0,-1.4,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(2,.8,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["wall2"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["goal"].model = Model("models/quad.obj");
	gameObjects["goal"].transform = {
		glm::vec3(1.8,0,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.5f,.5f,.5f),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["goal"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		true
	};
	gameObjects["goal"].collider = gameObjects["goal"].axisAlignedBoundingBox;

	gameObjects["player"].model = Model("models/sphere.obj");
	gameObjects["player"].transform = {
		glm::vec3(-1.8,0,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.5f,.5f,.5f),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["player"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		true
	};
	gameObjects["player"].collider = gameObjects["player"].axisAlignedBoundingBox;

	gameObjects["obs"].model = Model("models/box.obj");
	gameObjects["obs"].transform = {
		glm::vec3(-.4,.4,1),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.1,.1,.1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["obs"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["obs2"].model = Model("models/box.obj");
	gameObjects["obs2"].transform = {
		glm::vec3(.3,.4,1),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.1,.1,.1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["obs2"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};

}


Engine::~Engine()
{

}
