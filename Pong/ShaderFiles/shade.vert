#version 430

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTranslation;
layout(location = 3) in vec2 vRotation;

out vec3 fNormal;
out vec4 fColor;

void main()
{
	mat4 scale = mat4(  0.5f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.5f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );

	// rotate
	float rot_ang = vRotation.x;
	mat4 rotate_1 = mat4( cos(rot_ang), 0.0f, sin(rot_ang), 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-sin(rot_ang), 0.0f, cos(rot_ang), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	//rot_ang = 1.40f;
	rot_ang = vRotation.y;
	mat4 rotate_2 = mat4( cos(rot_ang), -sin(rot_ang), 0.0f, 0.0f,
						sin(rot_ang), cos(rot_ang), 0.0f, 0.0f,
						0.0f, 0.0f, 0.1f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f);
	mat4 rotate = rotate_2 * rotate_1;
	
	vec4 position = rotate * scale * vec4(vPosition, 1.0f);
	//vec4 position = scale * vec4(vPosition, 1.0f);
	position.x += vTranslation.x;
	position.y += vTranslation.y;
	

	gl_Position = position;
	//gl_Position = rotate * vec4(vPosition, 1.0f);
	//gl_Position = scale * vec4(vPosition, 1.0f);
	//gl_Position = vec4(vPosition, 1.0f);

	fNormal = normalize(vNormal);
	fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}