//#pragma once

#ifndef _PROGRAM
#define _PROGRAM

#include <GL/glew.h>
#include "Shader/Shader.h"

class Program
{
private:
	GLuint _id;

public:
	template<class T>
	friend struct std::hash;

	friend bool operator==(const Program& lho, const Program& rho);

public:
	Program();

	Program(const Program& other);

	Program(Program&& other) noexcept;

	Program& operator=(const Program& other);

	~Program();

	inline const GLuint GetId() const { return _id; }

	inline void AttachShader(GLuint shaderId) { glAttachShader(_id, shaderId); }

	inline void DetachShader(GLuint shaderId) { glDetachShader(_id, shaderId); }

	void Link() const;

	inline void Use() const { glUseProgram(_id); }
};

template<>
struct std::hash<Program>
{
	std::size_t operator()(const Program& key) const
	{
		return ((std::hash<GLuint>()(key._id))); //>> 1);
	}
};

#endif