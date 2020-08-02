#ifndef _ATTRIBUTE
#define _ATTRIBUTE

#include <GL/glew.h>

class Attribute 
{
	GLuint _index;
	GLenum _type;
	GLint _size;
	GLboolean _normalized;
	GLsizei _fullAttributeSize;

public:
	Attribute(GLuint index, GLenum type, GLint size, GLboolean normailzed, GLsizei fullAttributeSize);

	Attribute(const Attribute& other) = default;

	Attribute(Attribute&&) = default;

	//Attribute& operator=(const Attribute& other) = default;

	inline GLuint GetIndex() const { return _index; }

	inline GLenum GetType() const { return _type; }

	inline GLint GetSize() const { return _size; }

	inline GLboolean GetNormalized() const { return _normalized; }

	inline GLsizei GetFullAttributeSize() const { return _fullAttributeSize; }
};

#endif