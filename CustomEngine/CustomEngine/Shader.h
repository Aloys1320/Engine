#pragma 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>
#include <fstream>
#include <iostream>
class Shader
{
private:
	GLuint program;
	GLuint loadShader(const char* file, GLenum shaderType);
public:
	bool failStat;

	GLuint getprogram() const;
	bool loadShaders(const char* vertexFile, const char* fragmentFile);
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	~Shader();

};