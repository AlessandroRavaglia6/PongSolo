#include "DrawCallDrawElementsInstanced.h"

#include <iostream>

DrawCallDrawElementsInstanced::DrawCallDrawElementsInstanced() {}

DrawCallDrawElementsInstanced::~DrawCallDrawElementsInstanced() { std::cout << "DrawCallDrawElementsInstanced_Destructor" << std::endl; }

DrawCallDrawElementsInstanced::DrawCallDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount)
	: DrawCall(mode), _count(count), _type(type), _indices(indices), _primcount(primcount) {}

void DrawCallDrawElementsInstanced::Draw()
{
	glDrawElementsInstanced(_mode, _count, _type, _indices, _primcount);
}