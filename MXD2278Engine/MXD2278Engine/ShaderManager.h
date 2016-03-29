#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <fstream>
#include <iostream>
class ShaderManager
{
private:
	GLuint program;
	GLuint loadShader(const char* file, GLenum shaderType);

public:
	GLuint getprogram() const;
	bool loadShaders(const char* vertexFile, const char* fragmentFile);
	ShaderManager();
	~ShaderManager();
};

