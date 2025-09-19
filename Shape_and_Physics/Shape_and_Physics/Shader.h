#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cerrno>

std::string get_file_contant(const char* file);   // To convert a file into a char

class Shader
{
public:

	GLuint ID;

	Shader(const char* vertex_shader, const char* fragment_shader);

	void Activate();
	void Deactivate();

};


#endif // !SHADER_H



