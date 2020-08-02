#ifndef _VERTEX_ARRAY_OBJECT
#define _VERTEX_ARRAY_OBJECT

#include <GL/glew.h>

class VertexArrayObject
{
	friend class VertexArrayManager;

private:
	GLuint _id;

private:
	VertexArrayObject(GLuint id);

public:
	VertexArrayObject() = default;
	VertexArrayObject(const VertexArrayObject& other);
	VertexArrayObject(VertexArrayObject&& other) = default;

	VertexArrayObject& operator=(const VertexArrayObject& other);

	~VertexArrayObject() = default;

	GLuint GetId();
};

#endif