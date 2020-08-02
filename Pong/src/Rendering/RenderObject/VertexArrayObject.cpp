#include "VertexArrayObject.h"

#include "../../PreprocessorSettings.h"
#ifdef _STD_OUT
#include <iostream>
#endif

VertexArrayObject::VertexArrayObject(GLuint id) : _id(id) {}

VertexArrayObject::VertexArrayObject(const VertexArrayObject& other) : _id(other._id)
{
#ifdef _STD_OUT
	std::cout << "VertexArrayObject_Copy_Constructor";
#endif
}

VertexArrayObject& VertexArrayObject::operator=(const VertexArrayObject& other)
{
	this->_id = other._id;
	return *this;
}

GLuint VertexArrayObject::GetId() { return _id; }