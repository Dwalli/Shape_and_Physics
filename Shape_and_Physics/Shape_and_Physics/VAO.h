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

	void LinkVBO(GLuint Layout, VBO VBO);
	void Bind();
	void Unbind();
	void Deactivate();

};


#endif // !EBO_H



