#version 430

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 fNormal;
out vec4 fColor;

void main()
{
	mat4 scale = mat4(  0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.5f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );
	
	//gl_Position = scale * vec4(vPosition, 1.0f);
	gl_Position = vec4(vPosition, 1.0f);

	fNormal = normalize(vNormal);
	fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}