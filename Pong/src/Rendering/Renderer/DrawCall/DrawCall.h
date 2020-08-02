#ifndef _DRAW_CALL
#define _DRAW_CALL

#include <GL/glew.h>
#include <set>

class DrawCall // virtual
{
	friend class Renderer;

protected:
	//GLuint _id;

	GLenum _mode;

protected:

	DrawCall();

	virtual ~DrawCall() = 0;

	DrawCall(GLenum mode);

	virtual void Draw() = 0;
};
#endif