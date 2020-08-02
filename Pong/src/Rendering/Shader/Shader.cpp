#include "Shader.h"

#include "../../PreprocessorSettings.h"

#ifdef _STD_OUT
#include <iostream>
#endif

#include <fstream>
#include <unordered_map>
#include <GL/glew.h>

std::unordered_map<GLenum, std::string> shaderTypeMap
{
	{GL_VERTEX_SHADER, "GL_VERTEX_SHADER"},
	{GL_FRAGMENT_SHADER, "GL_FRAGMENT_SHADER"},
	{GL_TESS_CONTROL_SHADER, "GL_TESS_CONTROL_SHADER"},
	{GL_TESS_EVALUATION_SHADER, "GL_TESS_EVALUATION_SHADER"},
	{GL_GEOMETRY_SHADER, "GL_GEOMETRY_SHADER"}
};

Shader::Shader() : _id(-1) {}

Shader::Shader(Shader&& shader) : _id(shader._id)
{
	#ifdef _STD_OUT
	std::cout << "Shader_Move" << std::endl;
	#endif
}

Shader::Shader(const Shader& shader) : _id(shader._id)
{
	#ifdef _STD_OUT
	std::cout << "Shader_Copy_Constructor" << std::endl;
	#endif
}

Shader& Shader::operator=(const Shader& shader) 
{
	_id = shader._id;
	return *this;
}

Shader::Shader(GLenum type, const GLchar* const* sourceCode, GLsizei numLines)
{
	

	_id = glCreateShader(type);

	#ifdef _STD_OUT
	if(_id == 0) { std::cerr << "Error: glCreateShader" << std::endl; }
	else { std::cout << "Shader [" << shaderTypeMap[type] << "] created with id: " << _id << std::endl; }
	#endif

	glShaderSource(_id, numLines, sourceCode, nullptr);

	glCompileShader(_id);
	GLint operationResult;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &operationResult);
	if (operationResult != GL_TRUE)
	{
		#ifdef _STD_OUT
		std::cerr << "Error: glCompileShader" << std::endl;
		#endif

		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &operationResult);
		char* infoLog = new char[operationResult];
		GLint length;
		glGetShaderInfoLog(_id, operationResult, &length, infoLog);

		#ifdef _STD_OUT
		std::cerr << "Compilation log:\n" << infoLog << std::endl;
		#endif
	}
	else
	{
		#ifdef _STD_OUT
		std::cout << "Shader [" << shaderTypeMap[type] << "] compiled successfully" << std::endl;
		#endif
	}
}

Shader::~Shader()
{
	#ifdef _STD_OUT
	std::cout << "Shader_Destructor" << std::endl;
	#endif
}