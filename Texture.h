#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"
class Texture {
public:
	GLuint ID;
	unsigned char* bytes;
	GLuint unit;
	GLenum type;
	
	Texture(const char* imagePath, GLenum texType, GLuint slot, GLenum foramt, GLenum pixelType);
	void texSlotSetting(const Shader& shader, const char* uniform, GLuint slot);
	void Bind();
	void unBind();
	void Delete();
};