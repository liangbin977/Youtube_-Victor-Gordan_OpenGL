#include "VBO.h"
VBO::VBO(std::vector<Vertex>& vertices){
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); // introduce the vertex data into the buffer's memory
} //vector.data() returns a pointer to the underlying array serving as the vector's storage, which is what OpenGL expects for buffer data. The size of the data is calculated as the number of vertices multiplied by the size of a single Vertex struct, and GL_STATIC_DRAW indicates that the vertex data will be set once and used many times for drawing operations.
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::unBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}