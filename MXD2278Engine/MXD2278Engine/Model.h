#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <string>
#include <map>
#include "Texture.h"

class Model
{
private:
	std::map <int, GLuint> textures;
	Texture textureManager;
	int textureIds;
	unsigned int vertCount;
	GLuint vertArr;
	char* filePath;
public:
	char* getFilePath();
	bool buffer(std::string objFile);
	void render();
	void updateTexture();
	Model();
	Model(char* filePath);
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