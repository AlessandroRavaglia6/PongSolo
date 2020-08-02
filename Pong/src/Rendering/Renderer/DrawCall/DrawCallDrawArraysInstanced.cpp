#include "DrawCallDrawArraysInstanced.h"

#include <iostream>

DrawCallDrawArraysInstanced::DrawCallDrawArraysInstanced() {}

DrawCallDrawArraysInstanced::~DrawCallDrawArraysInstanced() { std::cout << "DrawCallDrawArraysInstanced_Destructor" << std::endl; }

DrawCallDrawArraysInstanced::DrawCallDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
	: DrawCall(mode), _first(first), _count(count), _instanceCount(instanceCount) {}

void DrawCallDrawArraysInstanced::Draw()
{
	glDrawArraysInstanced(_mode, _first, _count, _instanceCount);
}