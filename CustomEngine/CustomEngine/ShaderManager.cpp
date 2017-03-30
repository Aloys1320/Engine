#include "ShaderManager.h"



Shader ShaderManager::getShaders(int key) const
{
	return shaders.find(key)->second;
}

bool ShaderManager::createShader(char * vertPath, char * fragPath)
{
	shaders.emplace(0, Shader(vertPath,fragPath));
	if((shaders.find(0)->second.failStat))
		return false;
	else return true;
}

ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}
