#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
class Mesh
{
public:
	bool BufferModel(std::string objFile);
	Mesh();
	~Mesh();
};

