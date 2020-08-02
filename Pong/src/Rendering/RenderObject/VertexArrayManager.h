#ifndef _VERTEX_ARRAY_MANAGER
#define _VERTEX_ARRAY_MANAGER

#include <GL/glew.h>

#include "VertexArrayObject.h"

class VertexArrayManager 
{
private:
	static GLuint _currentVaoId;

public:
	VertexArrayManager() = delete;
	VertexArrayManager(const VertexArrayManager&) = delete;
	VertexArrayManager(VertexArrayManager&&) = delete;

	static inline VertexArrayObject GenVAO()
	{
		GLuint id;
		glGenVertexArrays(1, &id);
		return { id };
	}

	static inline void BindVAO(VertexArrayObject& vao) 
	{ if (vao._id != _currentVaoId) { glBindVertexArray(vao._id); _currentVaoId = vao._id; } }

	static inline void DeleteVAO(VertexArrayObject& vao) 
	{
		if (vao._id == _currentVaoId) { _currentVaoId = -1; }
		glDeleteVertexArrays(1, &(vao._id));
	}
};

#endif