#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLuint id, GLenum target) : _id(id), _target(target) {}

VertexBufferObject::VertexBufferObject(VertexBufferObject&& other) noexcept : _id(other._id), _target(other._target) {}

void VertexBufferObject::BufferData(GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(_target, size, data, usage);
}