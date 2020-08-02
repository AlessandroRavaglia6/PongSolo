#ifndef _VERTEX_BUFFER_OBJECT
#define _VERTEX_BUFFER_OBJECT

#include <GL/glew.h>

class VertexBufferObject 
{
	friend class VertexBufferManager;

private:
	GLuint _id;
	GLenum _target;

public:
	VertexBufferObject() = delete;
	VertexBufferObject(const VertexBufferObject& other) = default;
	VertexBufferObject(VertexBufferObject&& other) noexcept;

private:
	VertexBufferObject(GLuint id, GLenum target);

public:
	void BufferData(GLsizeiptr size, const void* data, GLenum usage);
};

#endif
