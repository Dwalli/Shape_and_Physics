#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// linking the vbo with the vao
void VAO::LinkAtribute(GLuint Layout, VBO& VBO, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(Layout, numComponents, type, GL_FALSE,stride, offset);
	glEnableVertexAttribArray(Layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Deactivate()
{
	glDeleteVertexArrays(1, &ID);
}
