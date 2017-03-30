#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <fstream>
#include <iostream>
#include "Shader.h"
#include <map>
class ShaderManager
{
private:
	//Shader shader;
	std::map<int, Shader> shaders;

public:
	Shader getShaders(int key) const;
	bool createShader(char* vertPath,char* fragPath);
	ShaderManager();
	~ShaderManager();
};

