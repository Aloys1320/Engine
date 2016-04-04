#include "Texture.h"

//Load a texture and assign a GLuint as a reference.
GLuint Texture::loadTexture(char * texturePath)
{	//Load Texture
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(texturePath, 0), texturePath);
	if (image == nullptr);
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);
	glGenTextures(1, &texId);

	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texId;
}

Texture::Texture()
{
}

Texture::~Texture()
{
}
