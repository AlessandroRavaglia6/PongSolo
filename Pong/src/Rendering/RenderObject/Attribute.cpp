#include "Attribute.h"

Attribute::Attribute(GLuint index, GLenum type, GLint size, GLboolean normalized, GLsizei fullAttributeSize)
	: _index(index), _type(type), _size(size), _normalized(normalized), _fullAttributeSize(fullAttributeSize) {}