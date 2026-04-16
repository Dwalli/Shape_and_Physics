#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include "Shader.h"


class Texture
{
public:
	GLuint ID;
	GLuint type;
	GLuint UID;
	//      image path,       texture type,    texture slot,  format of the pixel and the data type of the pixel
	Texture(const char* image, GLuint TexType, GLuint TexSlot, GLenum format, GLenum pixeltype);

	// Assigns a texture unit to a uniform
	void TextureUnit(Shader shadeer, const char* uniform, GLuint uniSlot);
	
	void Bind();
	void Unbind();
	void Deactivate();
private:
};


#endif 