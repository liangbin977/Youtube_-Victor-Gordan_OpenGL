#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shaderClass.h"
class Texture {
public:
	GLuint ID;
	unsigned char* bytes;
	Texture(const char* imagePath, GLenum texType, GLenum slot, GLenum foramt, GLenum pixelType);
	void texSlotSetting(const Shader& shader, const char* uniform, GLuint slot);
	void Bind();
	void unBind();
	void Delete();
};