#pragma once
#include "../Utilities/utilities.h"
class Texture
{
public:
	int width = 0, height = 0, bpp = 0;
	GLuint TextureId;
	void initTexture(char* fileName);
	Texture();
	~Texture();
};