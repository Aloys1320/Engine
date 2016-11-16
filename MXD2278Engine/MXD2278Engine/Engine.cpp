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
	//TODO: Move to Texture Manager. Have game objects manage their own textures
	gameObjects["wall"].model.loadTexture("wall","textures/wall.jpg");
	gameObjects["wall2"].model.loadTexture("wall", "textures/wall.jpg");
	gameObjects["wall3"].model.loadTexture("wall", "textures/wall.jpg");

	gameObjects["goal"].model.loadTexture("goal", "textures/goal.jpg");
	gameObjects["obs"].model.loadTexture("spike", "textures/red.png");
	gameObjects["obs2"].model.loadTexture("spike", "textures/dome.png");
	gameObjects["player"].model.loadTexture("player", "textures/mario.png");


	//Get GLFW Time
	currentTime=glfwGetTime();

	playButton.model.loadTexture("play","textures/TestTexture.png");
	bool play = true;
	int playerJumps = 1;
	// MAIN GAME LOOP
	while (!glfwWindowShouldClose(GLFWwindowPtr)) {

		playButton.updateModel(shaderManager.getprogram(),currentTime);
		//Active game loop
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glClear(GL_DEPTH_BUFFER_BIT);
			glClear(GL_COLOR_BUFFER_BIT);
			if (!play) {
				glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				mainCamera.camTransform.location = glm::vec3(0, 0, 2);
				mainCamera.camTransform.rotation = glm::vec3(0);
				std::cout << playButton.transform.location.x << " " << playButton.transform.location.y << " " << playButton.transform.location.z << std::endl;
			}
			//Update Times
			previousTime = currentTime;
			currentTime = glfwGetTime();
			deltaTime = currentTime - previousTime;
			if (play) {
				glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
			//Escape exits program
			if (keyIsDown[GLFW_KEY_ESCAPE]) {
				glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
				play = false;
			}
			//Camera Update

			//Camera Movement
			if (play) {
				//Mouse Detection
				float sens = .005;
				int w = 800, h = 600;
				double x, y;
				glfwGetCursorPos(GLFWwindowPtr, &x, &y);
				mainCamera.camTransform.rotation.y -= sens * (x - w * .5f); // Yaw
				mainCamera.camTransform.rotation.x -= sens * (y - h * .5f); // Pitch
				mainCamera.camTransform.rotation.x =
					glm::clamp(mainCamera.camTransform.rotation.x, -.5f * 3.14f, .5f * 3.14f);
				glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);

				mainCamera.camTransform.location = gameObjects["player"].transform.location;
				mainCamera.camTransform.location.y = gameObjects["player"].transform.location.y + 1.5*gameObjects["player"].transform.size.y;

				//Key Detection for Camera
				glm::vec3 camVel;
				glm::mat3 R = (glm::mat3)glm::yawPitchRoll(mainCamera.camTransform.rotation.y, 0.0f, 0.0f);

				if (keyIsDown[GLFW_KEY_A])
					gameObjects["player"].rigidBody.force += R * glm::vec3(-10, 0, 0);
				if (keyIsDown[GLFW_KEY_D])
					gameObjects["player"].rigidBody.force += R * glm::vec3(10, 0, 0);
				if (keyIsDown[GLFW_KEY_W])
					gameObjects["player"].rigidBody.force += R * glm::vec3(0, 0, -10);
				if (keyIsDown[GLFW_KEY_S])
					gameObjects["player"].rigidBody.force += R * glm::vec3(0, 0, 10);

				//if (keyWasDown[GLFW_KEY_A] && !keyIsDown[GLFW_KEY_A])
				//	gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);
				//if (keyWasDown[GLFW_KEY_D] && !keyIsDown[GLFW_KEY_D])
				//	gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);
				//if (keyWasDown[GLFW_KEY_W] && !keyIsDown[GLFW_KEY_W])
				//	gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);
				//if (keyWasDown[GLFW_KEY_S] && !keyIsDown[GLFW_KEY_S])
				//	gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);

				float speed = 10.f;
				if (camVel != glm::vec3())
					camVel = glm::normalize(camVel) * speed;
				mainCamera.camRigidBody.force = camVel;
			}
			mainCamera.updateCamera(shaderManager.getprogram(), deltaTime);


			//Character Movement
			//if (keyIsDown[GLFW_KEY_D])
			//	gameObjects["player"].rigidBody.force += glm::vec3(2,0,0);
			//if(keyWasDown[GLFW_KEY_D]&&!keyIsDown[GLFW_KEY_D])
			//	gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);
			//if (keyIsDown[GLFW_KEY_A])
			//	gameObjects["player"].rigidBody.force += glm::vec3(-2, 0, 0);
			//if (keyWasDown[GLFW_KEY_A] && !keyIsDown[GLFW_KEY_A])
			//	gameObjects["player"].rigidBody.velocity = glm::vec3(0, 0, 0);
			if (play) {
				if (keyIsDown[GLFW_KEY_SPACE] && !keyWasDown[GLFW_KEY_SPACE] && playerJumps > 0) {
					playerJumps--;
					gameObjects["player"].rigidBody.force += glm::vec3(0, 600, 0);
				}
			}
			//Lighting
			glm::vec3 lightLocation[2];
			lightLocation[0] = glm::vec3(gameObjects["obs"].transform.location.x,1.5, gameObjects["obs"].transform.location.z);
			lightLocation[1] = glm::vec3(gameObjects["obs2"].transform.location.x, 1.5, gameObjects["obs2"].transform.location.z);

			//std::cout << lightLocation.x << " "<< lightLocation .y <<" "<< lightLocation.z<< std::endl;

			//Location of a light in the game.
			glUniform3fv(glGetUniformLocation(shaderManager.getprogram(), "lightLoc"), 1, &lightLocation[0][0]);						//Location of the light in the game
			glUniform3fv(glGetUniformLocation(shaderManager.getprogram(), "camLoc"), 1, &mainCamera.camTransform.location[0]);		//Location of the camera. Passes in the camera location.

			//Collision Checks
			if (gameObjects["player"].collidesWith(gameObjects["goal"])) {
				std::cout << "Player has collided with the Goal" << std::endl;
				//gameObjects["player"].rigidBody.force *= -1;
				gameObjects["player"].rigidBody.velocity = glm::vec3(0);
			}
			if (gameObjects["player"].collidesWith(gameObjects["obs"]) || gameObjects["player"].collidesWith(gameObjects["obs2"])) {
				std::cout << "Player has collided with an Obstacle" << std::endl;
				//gameObjects["player"].rigidBody.force *= -1;
				gameObjects["player"].transform.location=glm::vec3(-7.8, 1, 0);
			}
			if (gameObjects["player"].collidesWith(gameObjects["wall2"])) {
				//std::cout << "TEST" << std::endl;
				playerJumps = 1;
				gameObjects["player"].rigidBody.velocity.y = 0;
			}
			if (gameObjects["obs"].collidesWith(gameObjects["wall"]) || gameObjects["obs"].collidesWith(gameObjects["wall3"])) {
				gameObjects["obs"].rigidBody.velocity *= -1;
				std::cout << "HIT WALL" << std::endl;
			}
			if (gameObjects["obs2"].collidesWith(gameObjects["wall"]) || gameObjects["obs2"].collidesWith(gameObjects["wall3"])) {
				gameObjects["obs2"].rigidBody.velocity *= -1;
				std::cout << "2 HIT WALL" << std::endl;
			}
			if (play) {

				gameObjects["obs2"].rigidBody.force += gameObjects["obs2"].rigidBody.velocity * 6.5f;
				gameObjects["obs"].rigidBody.force += gameObjects["obs"].rigidBody.velocity * 6.5f;

				//Update Section
				for (auto& mod : gameObjects)
				{
					if (mod.second.rigidBody.usesGravity) {
						if (mod.second.collidesWith(gameObjects["wall2"])) {

							//Apply normal force if object collieds with floor (N=w*cos(angle))
							mod.second.rigidBody.force += mod.second.rigidBody.mass*(glm::vec3(0, 9.8, 0));// *glm::cos(gameObjects["wall2"].transform.rotation));
							//mod.second.rigidBody.velocity.y = 0;
						}
						//if (mod.second.collidesWith(gameObjects["wall"])|| mod.second.collidesWith(gameObjects["wall3"])) {
						//	mod.second.rigidBody.velocity *= -1;
						//	std::cout << "HIT WALL" << std::endl;
						//}
					}
					mod.second.updateModel(shaderManager.getprogram(), deltaTime);
				}
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


	//Declare Game Objects (class later?)
	gameObjects = std::map<std::string, GameObject>();
	gameObjects["wall"].model = Model("models/box.obj");
	gameObjects["wall"].transform = {
		glm::vec3(0,0, -8),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(8,8,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["wall"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["wall"].collider = gameObjects["wall"].axisAlignedBoundingBox;
	gameObjects["wall3"].model = Model("models/box.obj");
	gameObjects["wall3"].transform = {
		glm::vec3(0,0, 8),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(8,8,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["wall3"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["wall3"].collider = gameObjects["wall3"].axisAlignedBoundingBox;
	gameObjects["wall2"].model = Model("models/box.obj");
	gameObjects["wall2"].transform = {
		glm::vec3(0,-1.4,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(8,.8,2),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["wall2"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["wall2"].collider = gameObjects["wall2"].axisAlignedBoundingBox;

	gameObjects["goal"].model = Model("models/quad.obj");
	gameObjects["goal"].transform = {
		glm::vec3(7.8,0,0),		//Position
		glm::vec3(0,1.5708,0),		//Rotation
		glm::vec3(.5f,.5f,.5f),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["goal"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1						//Mass
	};
	gameObjects["goal"].rigidBody.usesGravity = true;
	gameObjects["goal"].collider = gameObjects["goal"].axisAlignedBoundingBox;

	gameObjects["player"].model = Model("models/sphere.obj");
	gameObjects["player"].transform = {
		glm::vec3(-7.8,1,0),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(.5f,.5f,.5f),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["player"].rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
	};
	gameObjects["player"].rigidBody.usesGravity = true;
	gameObjects["player"].collider = gameObjects["player"].sphere;

	gameObjects["obs"].model = Model("models/teapot.obj");
	gameObjects["obs"].transform = {
		glm::vec3(-3.4,.4,1),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(1,1,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["obs"].rigidBody = {
		glm::vec3(0,0,3),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["obs"].collider = gameObjects["obs"].sphere;

	gameObjects["obs2"].model = Model("models/teapot.obj");
	gameObjects["obs2"].transform = {
		glm::vec3(2.3,.4,1),		//Position
		glm::vec3(0,0,0),		//Rotation
		glm::vec3(1,1,1),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	gameObjects["obs2"].rigidBody = {
		glm::vec3(0,0,-2.5),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1,						//Mass
		false
	};
	gameObjects["obs2"].collider = gameObjects["obs2"].sphere;
	playButton = GameObject();
	playButton.model = Model("models/box.obj");
	playButton.transform = {
		glm::vec3(0,0,0),		//Position
		glm::vec3(0,1.5708,0),		//Rotation
		glm::vec3(10,10,10),		//Size
		glm::mat4(1)			//Transform Matrix (set later)
	};
	playButton.rigidBody = {
		glm::vec3(0),			//Velocity
		glm::vec3(0, 0, 0),		//Force
		1						//Mass
	};

	return true;
}

//Buffer the models using the modelclass.
bool Engine::bufferModels()
{
	//Attempt to buffer the test model
	if (!(playButton.model.buffer("models/quad.obj"))) {
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

}


Engine::~Engine()
{

}
