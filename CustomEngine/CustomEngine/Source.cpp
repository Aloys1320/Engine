#include "Engine.h"
#include <iostream>
#include <unordered_map>

typedef void(*func)(void);
std::unordered_map<int, func> errorList;


#pragma region ErrorPrints

	void e1() {
		std::cout<< "There was an error in glfwInit"<<std::endl;
	}
	void e2() {
		std::cout << "There was an error with the window pointer" << std::endl;
	}
	void e3() {
		std::cout << "There was an error in glewInit" << std::endl;
	}
	void e4() {
		std::cout << "Shader Load Error" << std::endl;
	}
#pragma endregion

	void printError(int error) {
		errorList.find(error)->second();
		exit(error);
	}
//Engine construction. Return nonzero for errors
int main() {

	errorList.emplace(1, e1);
	errorList.emplace(2, e2);
	errorList.emplace(3, e3);
	errorList.emplace(4, e4);


	int returnError = 0;
	Engine engine = Engine();
	returnError = engine.init();
	if (returnError != 0)
		printError(returnError);
	returnError = engine.bufferModels();
	if (returnError!=0)
		printError(returnError);

	//Create clear color
	glClearColor(.392f, .584f, .929f, 1.0f);

	//Begin the game loop if the shaders loaded correctly
	returnError = engine.createShaders();
	if (returnError==0)
		engine.gameLoop();


	return returnError;
}

