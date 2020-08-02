//#pragma once

#ifndef _SHADER
#define _SHADER

#include <GL/glew.h>

#include <string>

class Shader 
{
private:
	GLuint _id;

public:
	Shader();
	Shader(const Shader& shader);
	Shader(Shader&& shader);
	Shader& operator=(const Shader& shader);
	Shader(GLenum type, const GLchar* const* sourceCode, GLsizei numLines);

	~Shader();

	inline GLuint GetId() { return _id; }
	inline GLuint GetId() const { return _id; }
};

#endif