#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 translate; //Instance

out vec4 vertexColor;

void main()
{
	vec4 position = vec4(aPos, 1.0);
	position.x -= translate.x; //Instance
	position.y -= translate.y; //Instance

	gl_Position = position;
	vertexColor = vec4(aCol, 1.0);
}