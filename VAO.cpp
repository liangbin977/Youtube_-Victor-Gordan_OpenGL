#include "VAO.h"
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponent, type, GL_FALSE, stride, offset);// specify how OpenGL should interpret the vertex data and where it should start reading the data from the buffer
	glEnableVertexAttribArray(layout);
	VBO.unBind();
}
void VAO::Bind() {
	glBindVertexArray(ID);
}
void VAO::unBind() {
	glBindVertexArray(0);
}
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}