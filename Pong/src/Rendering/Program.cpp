#include "../PreprocessorSettings.h"

#ifdef _STD_OUT
#include <iostream>
#endif

#include "Program.h"
#include "Shader/Shader.h"



Program::Program()
{
	_id = glCreateProgram();

	#ifdef _STD_OUT
	if (_id == 0) { std::cerr << "Error: glCreateProgram" << std::endl; }
	else { std::cout << "Program created with id: " << _id << std::endl; }
	#endif
}

Program::Program(const Program& other) : _id(other._id)
{
	#ifdef _STD_OUT
	std::cout << "Program_Copy_Constructor" << std::endl;
	#endif
}

Program::Program(Program&& other) noexcept : _id(std::move(other._id))
{
	#ifdef _STD_OUT
	std::cout << "Program_Move_Constructor" << std::endl;
	#endif
}

Program& Program::operator=(const Program& other)
{
	_id = other._id;

	#ifdef _STD_OUT
	std::cout << "Program_Operator=" << std::endl;
	#endif

	return *this;
}

Program::~Program() 
{
	#ifdef _STD_OUT
	std::cout << "Program_Destructor" << std::endl; 
	#endif
}

void Program::Link() const 
{
	glLinkProgram(_id);
	GLint operationResult;
	
	glGetProgramiv(_id, GL_LINK_STATUS, &operationResult);
	if (operationResult != GL_TRUE) 
	{
		#ifdef _STD_OUT
		std::cerr << "Error: glLinkProgram" << std::endl;
		#endif
		
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &operationResult);
		char* infoLog = new char[operationResult];
		GLint length;
		glGetProgramInfoLog(_id, operationResult, &length, infoLog);

		#ifdef _STD_OUT
		std::cerr << "ProgramLinking log:\n" << infoLog << std::endl;
		#endif
		
		glDeleteProgram(_id);
	}
	else 
	{
		#ifdef _STD_OUT
		std::cout << "Program [" << _id << "] linked successfully" << std::endl;
		#endif
	}
}

bool operator==(const Program& lho, const Program& rho)
{
	return lho._id == rho._id;
}
