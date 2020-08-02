#ifndef	_DRAW_CALL_DRAW_ARRAYS_INSTANCED
#define	_DRAW_CALL_DRAW_ARRAYS_INSTANCED

#include <GL/glew.h>

#include "DrawCall.h"

class DrawCallDrawArraysInstanced : public DrawCall 
{
	friend class Renderer;

protected:
	GLint _first;
	GLsizei _count;
	GLsizei _instanceCount;

protected:

	DrawCallDrawArraysInstanced();

	virtual ~DrawCallDrawArraysInstanced();

	DrawCallDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount);

	virtual void Draw();

	//friend struct std::hash<DrawCallDrawArrays>;
};

#endif