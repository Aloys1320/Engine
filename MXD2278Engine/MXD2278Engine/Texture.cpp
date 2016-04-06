#include "Texture.h"

//Load a texture and assign a GLuint as a reference.
GLuint Texture::loadTexture(char * texturePath)
{	
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(texturePath, 0), texturePath);
	if (image == nullptr);																	//check if image is not null
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);								//Convert image to 32bit version
	FreeImage_Unload(image);																//Unload original version from ram
	glGenTextures(1, &texId);
	
	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	FreeImage_Unload(image32Bit);															//Unload image from ram
	glBindTexture(GL_TEXTURE_2D, 0);														//Unbind texture
	std::cout << "Bound Texture: " << texturePath << " to id " << texId << std::endl;
	return texId;
}

Texture::Texture(char * texturePath)
{
	loadTexture(texturePath);
}

Texture::Texture()
{
}

Texture::~Texture()
{
}
