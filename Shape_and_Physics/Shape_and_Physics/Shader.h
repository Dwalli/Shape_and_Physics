#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include <cstdio>

std::string get_file_contents(const char* filename);   // To convert a file into a char

class Shader
{
public:

	GLuint ID;

	Shader(const char* vertex_shader, const char* fragment_shader);

	void Activate();
	void Deactivate();

};


#endif // !SHADER_H



