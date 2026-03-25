#include "Texture.h"
Texture::Texture(const char* imagePath, GLenum texType, GLuint slot, GLenum format, GLenum pixelType) {
	type = texType;
	//Texture part is relatively fixed
	int widthImage, heightImage, numColChannels;
	stbi_set_flip_vertically_on_load(true); // Set the flag to flip the image vertically when loading, which is often necessary because OpenGL's texture coordinate system has the origin at the bottom left corner, while many image formats have the origin at the top left corner.
	bytes = stbi_load(imagePath, &widthImage, &heightImage, &numColChannels, 0); // Load the image file "Texture.png" and store its width, height, and number of color channels in the respective variables. The pixel data is stored in the "bytes" variable as an array of unsigned characters.

	glGenTextures(1, &ID); // Generate a texture object and store its ID in the "Texture" variable
	glActiveTexture(GL_TEXTURE0 + slot); // choose which slot to activate
	unit = slot; // store the slot number in the "unit" variable for later use when setting the uniform variable in the shader program
	glBindTexture(texType, ID); // insert the texture object into the currently active slot and bind it to the GL_TEXTURE_2D target, making it the current 2D texture for subsequent texture operations

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Set the texture minifying function to GL_NEAREST (nearest neighbor filtering)
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Set the texture magnification function to GL_NEAREST (nearest neighbor filtering)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT); // Set the texture wrapping mode for the S (horizontal) coordinate to GL_REPEAT (repeat the texture)
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT); // Set the texture wrapping mode for the T (vertical) coordinate to GL_REPEAT (repeat the texture)

	GLenum srcFormat = (numColChannels == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(texType, 0, GL_RGBA, widthImage, heightImage, 0, srcFormat, pixelType, bytes); // Specify a two-dimensional texture image with the pixel data stored in the "bytes" variable. The texture is defined with the target GL_TEXTURE_2D, level of detail 0, internal format GL_RGBA, width and height specified by the respective variables, border 0, format GL_RGBA, data type GL_UNSIGNED_BYTE.
	glGenerateMipmap(texType); // Generate mipmaps for the currently bound texture object

	stbi_image_free(bytes); // Free the memory allocated for the pixel data of the image
	glBindTexture(texType, 0);
}
void Texture::texSlotSetting(const Shader& shader, const char* uniform, GLuint slot) {
	shader.Activate();// must activate the shader program before setting the uniform variable
	glUniform1i(glGetUniformLocation(shader.ID, uniform), slot);// Set the value of the "texSlot" uniform variable in the shader program to 0 (the texture unit GL_TEXTURE0)
}
void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit); // Activate the texture unit corresponding to the "unit" variable, which was set during the construction of the Texture object
	glBindTexture(type, ID);
}
void Texture::unBind() {
	glBindTexture(type, 0);
}
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}