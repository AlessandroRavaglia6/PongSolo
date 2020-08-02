#version 430

out vec4 f_Color;

in flat vec4 fColor;

void main()
{
	f_Color = fColor;
}