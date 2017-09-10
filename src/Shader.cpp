#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Shader.h"

std::string readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

Shader::Shader(const char* vertPath, const char* fragPath)
{
	shaderProgram = glCreateProgram();
	//Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertSource = readFile(vertPath);
	const GLchar *vc_str = vertSource.c_str();
	glShaderSource(vertexShader, 1, &vc_str, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cerr << "Failed to compile shader : " << vertPath << "!" << buffer;
		//exit(-1);
	}
	glAttachShader(shaderProgram, vertexShader);

	//Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragSource = readFile(fragPath);
	const GLchar *fc_str = fragSource.c_str();
	glShaderSource(fragmentShader, 1, &fc_str, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cerr << "Failed to compile shader : " << fragPath << "!" << buffer;
		//exit(-1);
	}
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::enable()
{
	glUseProgram(shaderProgram);
}

void Shader::disable()
{
	glUseProgram(0);
}