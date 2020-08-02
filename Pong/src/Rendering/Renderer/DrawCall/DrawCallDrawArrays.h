#ifndef _DRAW_CALL_DRAW_ARRAYS
#define _DRAW_CALL_DRAW_ARRAYS

#include "DrawCall.h"
//#include "../Renderer.h"

#include <GL/glew.h>

//void func() {glDrawArrays(}

// Possible to extend into glDrawArraysInstanced || glDrawArraysInstancedBaseInstace

class DrawCallDrawArrays : public DrawCall 
{
	friend class Renderer;

protected:
	GLint _first;
	GLsizei _count;

protected:

	DrawCallDrawArrays();

	virtual ~DrawCallDrawArrays();

	DrawCallDrawArrays(GLenum mode, GLint first, GLsizei count);

	virtual void Draw();

	//friend struct std::hash<DrawCallDrawArrays>;
};

#endif