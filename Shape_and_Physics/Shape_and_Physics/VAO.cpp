#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// linking the vbo with the vao
void VAO::LinkVBO(GLuint Layout, VBO& VBO)
{
	VBO.Bind();
	glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
