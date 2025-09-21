#pragma once
#ifndef EBO_H
#define EBO_H


#include <glad/glad.h>


class EBO
{
public:
	GLuint ID;

	EBO(GLuint* indices, GLsizeiptr size); // To crate the EBO of an shape

	void Bind();
	void Unbind();
	void Deactivate();
};

#endif // !EBO_H


