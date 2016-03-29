#include "ShaderManager.h"



GLuint ShaderManager::getprogram() const
{
	return program;
}

bool ShaderManager::loadShaders(const char * vertexFile, const char * fragmentFile)
{
	//Load shaders
	GLuint vShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vShader == 0)
		return 0;

	GLuint fShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fShader == 0)
		return 0;

	//Create shader program
	program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	//Confirm link
	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result != 0)
		return true; 

	//Link Failed
	GLint logLength;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	GLchar* logArray = new GLchar[logLength+1];
	glGetProgramInfoLog(program, logLength, 0, logArray);
	std::cout << logArray << std::endl;
	glDeleteShader(program);
	delete[] logArray;
	return false;
}

//Helper Method to open and read shaders.
GLuint ShaderManager::loadShader(const char * file, GLenum shaderType)
{
	GLuint shaderIndex;
	int fileLength;
	char* fileContents;
	//Read in the file in binary
	std::ifstream inFile(file, std::ios::binary);
	if (inFile.is_open()) {
		inFile.seekg(0, std::ios::end);
		fileLength = (int)inFile.tellg();
		inFile.seekg(0, std::ios::beg);
		fileContents = new char[fileLength + 1];
		inFile.read(fileContents, fileLength);
		fileContents[fileLength] = 0;
		inFile.close();
	}
	//If file was not found/read properly, output the error and close.
	else {
		std::cout << "Error Opening or Reading File." << std::endl;
		return 0;
	}
	shaderIndex = glCreateShader(shaderType);
	glShaderSource(shaderIndex,1,&fileContents,0);
	glCompileShader(shaderIndex);
	delete[] fileContents;
	//Get result of shader creation.
	GLint result;
	glGetShaderiv(shaderIndex,GL_COMPILE_STATUS,&result);
	if (result != 0) {
		return shaderIndex;
	}
	//If shader failed, print out error and return 0
	GLint logLength;
	glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &logLength);
	GLchar* logArray = new GLchar[logLength];
	glGetShaderInfoLog(shaderIndex, logLength, 0, logArray);
	glDeleteShader(shaderIndex);
	std::cout << logArray << std::endl;
	delete[] logArray;
	return 0;
}

ShaderManager::ShaderManager()
{
	program = 0;
}


ShaderManager::~ShaderManager()
{
}
