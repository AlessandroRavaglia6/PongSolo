#ifndef _VERTEX_BUFFER_MANAGER
#define _VERTEX_BUFFER_MANAGER

#include <GL/glew.h>
#include "VertexBufferObject.h"

class VertexBufferManager
{
private:
	static GLuint _currentVboId;

public:
	VertexBufferManager() = delete;
	VertexBufferManager(const VertexBufferManager&) = delete;
	VertexBufferManager(VertexBufferManager&&) = delete;

	static inline  VertexBufferObject GenVBO(GLenum target)
	{
		GLuint id;
		glGenBuffers(1, &id);
		return { id, target };
	}

	static inline void BindVBO(VertexBufferObject& vbo)
	{ if (vbo._id != _currentVboId) { glBindBuffer(vbo._target, vbo._id); _currentVboId = vbo._id; } }

	static inline void DeleteVBO(VertexBufferObject& vbo) 
	{
		if (vbo._id == _currentVboId) { _currentVboId = -1; }
		glDeleteBuffers(1, &(vbo._id));
	}
};

#endif;