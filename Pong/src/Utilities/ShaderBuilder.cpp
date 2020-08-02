#include "ShaderBuilder.h"

#include "../PreprocessorSettings.h"

#include "FileReader.h"

#include <vector>

ShaderBuilder::ShaderBuilder() : _shaderType(0), _shaderSourceCode(nullptr), _sourceCode(nullptr), _numLines(0) {}

ShaderBuilder& ShaderBuilder::AddShaderType(ShaderType shaderType) 
{
	_shaderType = shaderType;
	return *this;
}

ShaderBuilder& ShaderBuilder::AddShaderSourceCode(const std::string& fileName)
{
	FileReader fileReader(fileName);
	_shaderSourceCode = new char[fileReader.GetFileLenght() + 1]();

	std::vector<GLchar*> pointers{};
	pointers.push_back(_shaderSourceCode);
	for (int i = 0; i < fileReader.GetFileLenght(); ++i) 
	{
		fileReader >> _shaderSourceCode[i];
		if (_shaderSourceCode[i] == '\r') 
		{ 
			_shaderSourceCode[i] = '\n'; 
		}
		else if (_shaderSourceCode[i] == '\n') 
		{ 
			++_numLines; 
			_shaderSourceCode[i] = '\0';
			pointers.push_back((&_shaderSourceCode[i]) + 1);
		}
	}
	++_numLines;
	_shaderSourceCode[fileReader.GetFileLenght()] = '\0';

	_sourceCode = new char*[_numLines]();
	for (int i = 0; i < _numLines; ++i) 
	{
		_sourceCode[i] = pointers[i];
	}

	return *this;
}

ShaderBuilder& ShaderBuilder::AddShaderSourceCode(std::string&& fileName)
{
	FileReader fileReader(fileName);
	_shaderSourceCode = new char[fileReader.GetFileLenght() + 1]();

	std::vector<GLchar*> pointers{};
	pointers.push_back(_shaderSourceCode);

	for (int i = 0; i < fileReader.GetFileLenght(); ++i)
	{
		fileReader >> _shaderSourceCode[i];
		if (_shaderSourceCode[i] == '\r')
		{
			_shaderSourceCode[i] = '\n';
		}
		else if (_shaderSourceCode[i] == '\n')
		{
			++_numLines;
			_shaderSourceCode[i] = '\0';
			pointers.push_back((&_shaderSourceCode[i]) + 1);
		}
	}
	++_numLines;
	_shaderSourceCode[fileReader.GetFileLenght()] = '\0';

	_sourceCode = new char*[_numLines]();
	for (int i = 0; i < _numLines; ++i)
	{
		_sourceCode[i] = pointers[i];
	}

	return *this;
}



Shader ShaderBuilder::BuildShader() 
{
	Shader out{ _shaderType, _sourceCode, _numLines };
	delete[](_shaderSourceCode); _shaderSourceCode = nullptr;
	delete[](_sourceCode); _sourceCode = nullptr;
	_shaderType = 0;
	_numLines = 0;
	return static_cast<Shader&&>(out);
}