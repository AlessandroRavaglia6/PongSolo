#ifndef _SHADER_SOURC_CODE
#define _SHADER_SOURC_CODE

#include <GL/glew.h>
#include <string>

class ShaderSourceCode 
{
private:
	GLchar** _sourceCode;
	GLsizei _numLines;

public:
	ShaderSourceCode(std::string& fileName);
	ShaderSourceCode(std::string&& fileName);

	~ShaderSourceCode();

	const GLchar* const* GetSourceCode();

	GLsizei GetNumLines();
};

#endif