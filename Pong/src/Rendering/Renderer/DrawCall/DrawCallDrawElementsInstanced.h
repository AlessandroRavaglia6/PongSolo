#ifndef	_DRAW_CALL_DRAW_ELEMENTS_INSTANCED
#define	_DRAW_CALL_DRAW_ELEMENTS_INSTANCED

#include <GL/glew.h>
#include "DrawCall.h"

class DrawCallDrawElementsInstanced : public DrawCall
{
	friend class Renderer;
	friend class RenderObject;

protected:
	GLsizei _count;
	GLenum _type;
	const void* _indices;
	GLsizei _primcount;

protected:

	DrawCallDrawElementsInstanced();

	virtual ~DrawCallDrawElementsInstanced();

	DrawCallDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount);

	virtual void Draw();

	//friend struct std::hash<DrawCallDrawArrays>;
};


#endif
