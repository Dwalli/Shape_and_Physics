#pragma once
#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint ID;

	VAO();

	void LinkAtribute(VBO& VBO, GLuint Layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Deactivate();

};


#endif // !VAO_H



