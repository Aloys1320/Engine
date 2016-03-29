#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
class Model
{
private:
	unsigned int vertCount;
	GLuint vertArr;

public:
	bool buffer(std::string objFile);
	void render();
	Model();
	~Model();
};

//Vertex structure to organize model information
struct Vertex {
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};

//Index structure to locate information
struct VertInd {
	unsigned int locInd;
	unsigned int uvInd;
	unsigned int normInd;
};