#pragma once
#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
public:
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size); // To crate the VBO of an shape

	void Bind();
	void Unbind();
	void Deactivate();
};

#endif // !VBO_H



