#include "DrawCallDrawArrays.h"

#include <iostream>

DrawCallDrawArrays::DrawCallDrawArrays() {}

DrawCallDrawArrays::~DrawCallDrawArrays() { std::cout << "DrawCallDrawArrays_Destructor" << std::endl; }

DrawCallDrawArrays::DrawCallDrawArrays(GLenum mode, GLint first, GLsizei count)
	: DrawCall(mode), _first(first), _count(count) {}

void DrawCallDrawArrays::Draw() 
{
	glDrawArrays(_mode, _first, _count);
}