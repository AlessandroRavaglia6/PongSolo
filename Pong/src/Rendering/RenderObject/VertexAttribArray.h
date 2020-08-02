#ifndef _VERTEX_ATTRIB_ARRAY
#define _VERTEX_ATTRIB_ARRAY

#include <GL/glew.h>
#include <vector>

#include "Attribute.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

class VertexAttribArray
{
private:
	GLsizei _stride;
	std::vector<Attribute> _attributes;

public:
	VertexAttribArray() = default;
	VertexAttribArray(const VertexAttribArray&) = default;
	VertexAttribArray(VertexAttribArray&&) = default;
	~VertexAttribArray() = default;

	const std::vector<Attribute>& GetAttributes();

	void AddAttribute(Attribute& attribute);

	void AddAttribute(Attribute&& attribute);

	void Enable(VertexArrayObject& vao, VertexBufferObject& vbo);

	void EnableInstanced(VertexArrayObject& vao, VertexBufferObject& vbo, GLsizei instanceCount);

	GLsizei VertexSize();
};

#endif
