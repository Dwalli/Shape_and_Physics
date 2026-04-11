#include "Texture.h"

Texture::Texture(const char* image, GLuint TexType, GLuint TexSlot, GLenum format, GLenum pixeltype)
{
	//Texturs
	type = TexType;
	int widthImage, heightImage, numColChanels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImage, &heightImage, &numColChanels, 0);
	if (bytes == nullptr)
	{
		std::cout << "Failed to load texture: " << image << std::endl;
		return;
	}

	glGenTextures(1, &ID);
	glActiveTexture(TexSlot);
	glBindTexture(type, ID);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(type, 0, format, widthImage, heightImage, 0, format, pixeltype, bytes);
	glGenerateMipmap(type);

	stbi_image_free(bytes);
	glBindTexture(type, 0);
}

void Texture::TextureUnit(Shader shadeer, const char* uniform, GLuint uniSlot)
{
	GLint textureUniform = glGetUniformLocation(shadeer.ID, uniform);
	shadeer.Activate();
	glUniform1i(textureUniform, uniSlot);
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
