#ifndef _DATA_PROCESSOR_SHADER
#define _DATA_PROCESSOR_SHADER

#include <GL/glew.h>

#include "../Rendering/Shader/Shader.h"
#include "../Rendering/Shader/ShaderType.h"

#include <string>

class ShaderBuilder 
{
private:
	GLenum _shaderType;
	GLchar* _shaderSourceCode;
	GLchar** _sourceCode;
	GLsizei _numLines;

public:
	ShaderBuilder();

	ShaderBuilder& AddShaderType(ShaderType shaderType);

	ShaderBuilder& AddShaderSourceCode(const std::string& fileName);

	ShaderBuilder& AddShaderSourceCode(std::string&& fileName);

	Shader BuildShader();

	char** GetSourceCode() { return _sourceCode; }
	int GetNumLines() { return _numLines; }
	void Reset() {
		delete[](_shaderSourceCode); _shaderSourceCode = nullptr;
		delete[](_sourceCode); _sourceCode = nullptr;
		_shaderType = 0;
		_numLines = 0;
	}

	// TEST
	ShaderBuilder& Test();
};

#endif