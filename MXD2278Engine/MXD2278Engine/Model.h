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
	std::vector<std::string> textureReference;
	int textureIds;
	unsigned int vertCount;
	GLuint vertArr;
	std::string filePath;
public:
	std::map <std::string, Texture> textures;

	std::string getFilePath();
	bool buffer(std::string objFile);
	void render();
	void updateTexture();
	void loadTexture(std::string,char* );
	Model();
	Model(std::string filePath);
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

//Transform Struct
struct Transform {
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 size;
	glm::mat4 worldTrans;
};