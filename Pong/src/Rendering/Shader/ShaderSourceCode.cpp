#include "ShaderSourceCode.h"

#include "../../PreprocessorSettings.h"

#ifdef _STD_OUT
#include <iostream>
#endif

#include <fstream>
#include <vector>

ShaderSourceCode::ShaderSourceCode(std::string& fileName)
{
	std::ifstream inFile;
	inFile.open(fileName);

	if (!inFile)
	{
		#ifdef _STD_OUT
		std::cerr << "Error: unable to open file [" << fileName << "]" << std::endl;
		#endif
		return;
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(inFile, line))
	{
		lines.push_back(line);
	}

	inFile.close();

	_sourceCode = new GLchar*[lines.size()];
	_numLines = lines.size();
	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		_sourceCode[i] = new GLchar[lines[i].length() + 2];
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			_sourceCode[i][j] = lines[i][j];
		}
		_sourceCode[i][lines[i].length()] = '\n';
		_sourceCode[i][lines[i].length() + 1] = '\0';
	}
}

ShaderSourceCode::ShaderSourceCode(std::string&& fileName)
{
	std::ifstream inFile;
	inFile.open(fileName);

	if (!inFile)
	{
		#ifdef _STD_OUT
		std::cerr << "Error: unable to open file [" << fileName << "]" << std::endl;
		#endif
		return;
	}

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(inFile, line))
	{
		lines.push_back(line);
	}

	inFile.close();

	_sourceCode = new GLchar*[lines.size()];
	_numLines = lines.size();
	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		_sourceCode[i] = new GLchar[lines[i].length() + 2];
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			_sourceCode[i][j] = lines[i][j];
		}
		_sourceCode[i][lines[i].length()] = '\n';
		_sourceCode[i][lines[i].length() + 1] = '\0';
	}
}

ShaderSourceCode::~ShaderSourceCode()
{
	#ifdef _STD_OUT
	std::cout << "_____________ShaderSourceCode_Delete" << std::endl;
	#endif
	delete[](_sourceCode);
}

const GLchar* const* ShaderSourceCode::GetSourceCode() { return _sourceCode; }

GLsizei ShaderSourceCode::GetNumLines() { return _numLines; }
