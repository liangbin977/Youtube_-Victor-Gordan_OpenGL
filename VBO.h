#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texCoord;
};
class VBO {
public:
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);
	VBO(std::vector<glm::mat4>& instanceMatrix);
	void Bind();
	void unBind();
	void Delete();
};