#include "Texture.h"

Texture::Texture(const char* image, GLuint TexType, GLuint TexSlot, GLenum format, GLenum pixeltype)
{
	//Texturs
	int widthImage, heightImage, numColChanels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImage, &heightImage, &numColChanels, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(TexSlot);
	glBindTexture(TexType, texture);

	glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(TexType, 0, format, widthImage, heightImage, 0, format, pixeltype, bytes);
	glGenerateMipmap(TexType);

	stbi_image_free(bytes);
	glBindTexture(TexType, 0);
}

void Texture::TextureUnit(Shader shadeer, const char* uniform, GLuint uniSlot)
{
	uniSlot = glGetUniformLocation(shadeer.ID, uniform);
	shadeer.Activate();
	glUniform1i(uniSlot, 0);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Deactivate()
{
	glDeleteTextures(1, &ID);
}
