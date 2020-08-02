#include "DrawCall.h"

#include <iostream>

DrawCall::DrawCall() {}

DrawCall::~DrawCall() { std::cout << "DrawCall_Destructor" << std::endl; }

DrawCall::DrawCall(GLenum mode) : _mode(mode) {}

//void DrawCall::Draw() {}